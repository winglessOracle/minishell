/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/20 12:53:29 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
		path = ft_strdup(cmd_args[0]);
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
	execve(cmd_args[0], cmd_args, env);
	exit_error("unknown command", 127);
}


int	set_fd(t_pipe *pipeline, t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe)
{
	int	count;

	count = 0;
	while (smpl_cmd->redirect)
	{
		if (smpl_cmd->redirect->type == OUTPUT)
		{
			if (access(smpl_cmd->redirect->content, F_OK) == 0)
				return (return_error("ccs: not allowed to overwrite file\n", 1));
			fd_pipe[1] = open(smpl_cmd->redirect->content, \
								O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd_pipe[1] < 0)
				return (return_perror("ccs:opening outfile", 1));
			count = 1;
		}
		else if (smpl_cmd->redirect->type == INPUT)
		{
			close(*keep);
			*keep = open(smpl_cmd->redirect->content, O_RDONLY);
			if (*keep < 0)
				return (return_perror("ccs:opening keep", 1));
		}
		else if (smpl_cmd->redirect->type == APPEND)
		{
			close(fd_pipe[1]);
			fd_pipe[1] = open(pipeline->pipe_argv->redirect->content, \
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd_pipe[1] < 0)
				return (return_perror("ccs: opening outfile", 1));
			count = 1;
		}
		else if (smpl_cmd->redirect->type == HEREDOC || smpl_cmd->redirect->type == HEREDOCQ)
			here_doc(pipeline, keep);
		if (*keep == -1 || fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (return_perror("fd:", 1));
		remove_node(&smpl_cmd->redirect, NULL);
	}
	return (count);
}
void	assignments(t_smpl_cmd *pipe_argv, pid_t pid)
{
	{
		if (pid == 0)
		{
			while (pipe_argv->assign)
			{
				add_variable(pipe_argv->env_list, \
							ft_strdup(pipe_argv->assign->content), 1);
				remove_node(&pipe_argv->assign, NULL);
			}
		}
	}
}

void	redirect(t_pipe *pipeline, pid_t pid, int keep, int *fd_pipe)
{
	int	set_out;

	if (pid == 0)
	{
		close(fd_pipe[0]);
		set_out = set_fd(pipeline, pipeline->pipe_argv, &keep, fd_pipe);
		if (set_out == -1)
			exit(1);
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

void		executor(t_pipe *pipeline)
{
	char	**env;
	pid_t	pid[pipeline->pipe_argc];
	int		fd_pipe[2];
	int		keep;
	int		i;

	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
	while (pipeline && pipeline->pipe_argv)
	{
		if (pipeline->pipe_argc == 1)
		{
			check_built(pipeline->pipe_argv);
			if (pipeline->pipe_argv->cmd_argc == 0)
			{
				assignments(pipeline->pipe_argv, 0);
				set_fd(pipeline, pipeline->pipe_argv, &keep, fd_pipe);
				return ;
			}
		}
		if (pipe(fd_pipe) == -1)
			exit_error("pipe fail", errno);
		env = get_env(pipeline->pipe_argv->env_list);
		i = 0;
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("fork fail", errno);
		redirect(pipeline, pid[i], keep, fd_pipe);
		assignments(pipeline->pipe_argv, pid[i]);
		if (pipeline->pipe_argv->cmd_argc > 0)
		{
			if (pid[i] == 0)
				exec_cmd(pipeline->pipe_argv, env);
		}
		else
		{
		 	if (pid[i] == 0)
				execute_exit(NULL, pipeline->pipe_argv->env_list);
		}
		pipeline->pipe_argv = pipeline->pipe_argv->next;
		i++;
	}
	set_exit_st(pipeline->pipe_argc, pid);
	// clean lists
}
