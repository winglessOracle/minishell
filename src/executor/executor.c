/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/19 09:34:08 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	exec_default(char **cmd_args, t_node *env_list, char **env)
{
	char	*path;
	char	**my_directories;
	int		i;

	i = 0;
	path = get_variable(env_list, "PATH");
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
	return (execve(cmd_args[0], cmd_args, env));
}

void	exec_cmd(t_pipe *pipeline, t_smpl_cmd *pipe_argv)
{
	char	**cmd_args;
	char	**env;

	check_built(pipeline, pipe_argv);
	cmd_args = build_cmd_args(&pipe_argv->cmd_argv, pipe_argv->cmd_argc);
	env = get_env(pipe_argv->env_list);
	if (cmd_args[0][0] == '.' && !cmd_args[0][1])
		exit_error_child("filename argument required", 2);
	if (cmd_args[0][0] == '/' || cmd_args[0][0] == '.')
	{
		check_cmd(cmd_args[0]);
		execve(cmd_args[0], cmd_args, env);
	}
	else
		exec_default(cmd_args, pipe_argv->env_list, env);
	lstclear(&pipe_argv->env_list, delete_content);
	delete_pipe(pipeline);
	ft_fprintf(2, "cc: ");
	perror("executor");
	_exit(127);
}

void	redirect(t_smpl_cmd *cmd, pid_t pid, int keep, int *fd_pipe)
{
	if (pid == 0)
	{
		if (set_fd(cmd, &keep, fd_pipe) == -1)
			exit_error_child("redirect", 1);
		close(fd_pipe[0]);
		dup2(keep, STDIN_FILENO);
		if (!keep)
			exit_error_child("dup fail", 1);
		if (!(!cmd->next && !set_fd(cmd, &keep, fd_pipe)))
			dup2(fd_pipe[1], STDOUT_FILENO);
		if (!fd_pipe[1])
			exit_error_child("dup fail", 1);
	}
	else
	{	
		close(keep);
		if (cmd->next)
			keep = dup(fd_pipe[0]);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (cmd->here_doc)
			close(cmd->here_doc);
	}
}

void	execute_child(t_pipe *pipeline, t_smpl_cmd *temp)
{
	signal(SIGQUIT, SIG_DFL);
	if (temp->cmd_argc > 0)
		exec_cmd(pipeline, temp);
	else
	{
		lstclear(&temp->env_list, delete_content);
		delete_pipe(pipeline);
		execute_exit(NULL, temp->env_list);
	}
}

void	executor(t_pipe *pipeline)
{
	pid_t		*pid;
	int			fd_pipe[2];
	int			keep;
	int			i;
	t_smpl_cmd	*temp;

	i = 0;
	temp = pipeline->pipe_argv;
	keep = init_keep();
	pid = init_pid(pipeline->pipe_argc);
	while (pipeline && temp)
	{
		if (check_and_pipe(pipeline, pid, fd_pipe))
			break ;
		pid[i] = fork();
		if (pid[i] == -1)
			return (fork_error());
		redirect(temp, pid[i], keep, fd_pipe);
		assignments(temp, pid[i]);
		if (pid[i] == 0 && pipeline->pipe_argc)
			execute_child(pipeline, temp);
		temp = temp->next;
		i++;
	}
	set_exit_st(pipeline->pipe_argc, pid);
}
