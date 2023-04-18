/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/18 09:25:07 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"
#include "builtin.h"

#define TMP_FILE "log/here_doc_tmp"
/*
0. add exit
1. add redirects
3. get right exitstatus
4. fix readline
*/


int	check_built(t_smpl_cmd *cmd)
{
	char	*builtings[6] =	{"echo", "cd", "pwd", "export",	"unset", "env"};
	int		i;
	t_built	*built[6];
	char	**cmd_args;

	built[0] = execute_echo;
	built[1] = execute_cd;
	built[2] = execute_pwd;
	built[3] = execute_export;
	built[4] = execute_unset;
	// built[5] = execute_env;
	i = 0;
	while (i < 6 && cmd->cmd_argc > 0)
	{
		if (ft_strcmp(cmd->cmd_argv->content, "exit") == 0)
		{
			cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
			execute_exit(cmd_args);
		}
		if (ft_strcmp(cmd->cmd_argv->content, builtings[i]) == 0)
		{
			cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
			if (!cmd_args)
				exit_error("building commands", 1);
			return (built[i](cmd_args, cmd->env_list));
		}
		i++;
	}
	return (-1);
}

void	exec_cmd(t_smpl_cmd *pipe_argv, char **env)
{
	char	**my_directories;
	char	**cmd_args;
	char	*path;
	int		i;

	i = 0;
	cmd_args = build_cmd_args(pipe_argv->cmd_argv, pipe_argv->cmd_argc);
	if (!cmd_args)
		exit_error("building commands", 1);
	path = get_variable(pipe_argv->env_list, "PATH");
	if (!path)
		execve(cmd_args[0], cmd_args, env);
	my_directories = ft_split(path, ':');
	ft_free(path);
	while (my_directories[i])
	{
		path = ft_strjoin(my_directories[i], "/");
		path = ft_strjoin_free_s1(path, cmd_args[0]);
		execve(path, cmd_args, env);
		ft_free(path);
		i++;
	}
	ft_free_array(my_directories);
	exit_error("unknown command", 127);
}

void	assignments(t_smpl_cmd *pipe_argv, pid_t pid)
{
	{
		if (pid == 0)
		{
			while (pipe_argv->assign)
			{
				add_variable(pipe_argv->env_list, ft_strdup(pipe_argv->assign->content), 1);
				remove_node(&pipe_argv->assign, NULL);
			}
		}
	}
}

void	here_doc(t_pipe *pipeline, int *keep)
{
	t_node	*tokens;
	char	*line_read;

	close(*keep);
	*keep = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*keep < 0)
		exit_error("opening tmp file", 1);
	while (1)
	{
		line_read = readline("here_doc ");
		if (!ft_strcmp(line_read, pipeline->pipe_argv->redirect->content))
		{
			unlink(TMP_FILE);
			exit(0) ;
		}
		ft_putstr_fd(line_read, *keep);
		free(line_read);
	}
	//	tokens = lexer(line_read, "|<> \t\n");
	//	while (tokens)
	//	{
	//		ft_putstr_fd(tokens->content, *keep);
	//		printf("token=%s\n", tokens->content);
	//		remove_node(&tokens, NULL);
	//	}
}

int	set_fd(t_pipe *pipeline, t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe)
{
	int	count;

	count = 0;
	while(smpl_cmd->redirect)
	{
		if (smpl_cmd->redirect->type == OUTPUT)
		{
			if (access(smpl_cmd->redirect->content, F_OK) == 0)
				return (-2);
			fd_pipe[1] = open(smpl_cmd->redirect->content, \
								O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd_pipe[1] < 0)
				exit_error("opening outfile", 1);
			count = 1;
		}
		else if (smpl_cmd->redirect->type == INPUT)
		{
			close(*keep);
			*keep = open(smpl_cmd->redirect->content, O_RDONLY);
			if (*keep < 0)
				exit_error("opening keep", 1);
		}
		else if (smpl_cmd->redirect->type == APPEND)
		{
			close(fd_pipe[1]);
			fd_pipe[1] = open(pipeline->pipe_argv->redirect->content, \
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd_pipe[1] < 0)
				exit_error("opening outfile", 1);
			count = 1;
		}
		else if (smpl_cmd->redirect->type == HEREDOC)
			here_doc(pipeline, keep);
		if (*keep == -1 || fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (-1);
		remove_node(&smpl_cmd->redirect, NULL);
	}
	return (count);
}

void	redirect(t_pipe *pipeline, pid_t pid, int keep, int *fd_pipe)
{
	int	set_out;

	if (pid == 0)
	{
		close(fd_pipe[0]);
		set_out = set_fd(pipeline, pipeline->pipe_argv, &keep, fd_pipe);
		if (set_out == -2)
			exit_error("cannot overwrite existing file", 1);
		if (set_out == -1)
			exit_error("No such file or directory", 1); //in case of no arguments this should return too
		dup2(keep, STDIN_FILENO);
		if (!keep)
			exit_error("dup fail", 1);
		if (!(!pipeline->pipe_argv->next && !set_out))
			dup2(fd_pipe[1], STDOUT_FILENO);
		if (!fd_pipe[1])
			exit_error("dup fail", 1);
	}
	else
	{	
		close(keep);
		if (pipeline->pipe_argv->next)
			keep = dup(fd_pipe[0]);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

int		executor(t_pipe *pipeline)
{
	int		keep;
	int		fd_pipe[2];
	pid_t	pid;
	char	**env;
	int		ret;

	ret = 0;
	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
	while (pipeline && pipeline->pipe_argv)
	{
		if (pipeline->pipe_argc == 1)
		{
			ret = check_built(pipeline->pipe_argv);
			if (ret != -1)
				return (ret);
			if (pipeline->pipe_argv->cmd_argc == 0)
			{
				assignments(pipeline->pipe_argv, 0);
				set_fd(pipeline, pipeline->pipe_argv, &keep, fd_pipe);
				return (0);
			}
		}
		if (pipe(fd_pipe) == -1)
			exit_error("pipe fail", errno);
		env = get_env(pipeline->pipe_argv->env_list);
		pid = fork();
		if (pid == -1)
			exit_error("fork fail", errno);
		redirect(pipeline, pid, keep, fd_pipe);
		assignments(pipeline->pipe_argv, pid);
		if (pipeline->pipe_argv->cmd_argc > 0)
		{
			if (pid == 0)
				exec_cmd(pipeline->pipe_argv, env);
			ret = get_exit_st(pipeline->pipe_argc, pid);
		}
		else if (pid == 0)
			exit(0);
		pipeline->pipe_argv = pipeline->pipe_argv->next;
	}
	return (ret);
	// clean lists 
}