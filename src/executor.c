/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/18 12:43:01 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"
#include "builtin.h"
/*
0. add builtings
1. add redirects
3. get right exitstatus
*/

int	check_built(t_smpl_cmd *cmd)
{
	char	*builtings[7] =	{"echo", "cd", "pwd", "export",	"unset", "env",	"exit"};
	int		i;
	t_built	*built[7];
	char	**cmd_args;

	built[0] = execute_echo;
	built[1] = execute_cd;
	built[2] = execute_pwd;
	built[3] = execute_export;
	built[4] = execute_unset;
	built[5] = execute_env;
	// built[6] = execute_exit;	2
	//printf("in check built\n");
	i = 0;
	while (i < 7 && cmd->cmd_argc > 0)
	{
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
	execve(cmd_args[0], cmd_args, env);
	ft_free(my_directories);
	exit_error("unknown command", 127);
}

void	assignments(t_smpl_cmd *pipe_argv, pid_t pid)
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

int	set_fd(t_pipe *pipeline, t_smpl_cmd *smpl_cmd, int *fd_keep, int *fd_pipe)
{
	while(smpl_cmd->redirect)
	{
		if (smpl_cmd->redirect->type == INPUT)
			*fd_keep = open(smpl_cmd->redirect->content, O_RDONLY);
		else if (smpl_cmd->redirect->type == OUTPUT)
			fd_pipe[1] = open(smpl_cmd->redirect->content, O_WRONLY);
		else if (smpl_cmd->redirect->type == APPEND)
			fd_pipe[1] = open(pipeline->pipe_argv->redirect->content, O_APPEND);
//		else if (pipe->redirect->type == HEREDOC)
		if (fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (-1);
		remove_node(&smpl_cmd->redirect, NULL);
	}
	return (0);
}

void	redirect(t_pipe *pipeline, pid_t pid, int fd_keep, int *fd_pipe)
{
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_keep, STDIN_FILENO);
		if (!fd_keep)
			exit_error("dup fail", 1);
		if (pipeline->pipe_argv->next)
			dup2(fd_pipe[1], STDOUT_FILENO);
		if (!fd_pipe[1])
			exit_error("dup fail", 1);
	//	if (set_fd(pipeline, pipeline->pipe_argv, &fd_keep, fd_pipe) != 0) //input rediret causes par and child to coexist
	//		perror("No such file or directory\n");
	}
	else
	{	
		close(fd_keep);
		if (pipeline->pipe_argv->next)
			fd_keep = dup(fd_pipe[0]);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

int		executor(t_pipe *pipeline)
{
	int		exitstatus;
	int		keep;
	int		fd_pipe[2];
	pid_t	pid;
	char	**env;
	int		ret;

	exitstatus = 0;
	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
	while (pipeline && pipeline->pipe_argv)
	{
			// printf("here argc: %d\n", pipeline->pipe_argv->cmd_argc);
		if (pipeline->pipe_argc == 1)
		{
			ret = check_built(pipeline->pipe_argv);
			if (ret != -1)
				return (ret);
			if (pipeline->pipe_argv->cmd_argc == 0)
			{
				assignments(pipeline->pipe_argv, 0);
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
			exitstatus = get_exit_st(pid);
		}
		else if (pid == 0)
			exit(0);
		pipeline->pipe_argv = pipeline->pipe_argv->next;
		// ft_free_array(env);
	}
	return (exitstatus);
	// clean lists 
}