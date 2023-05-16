/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/16 10:25:53 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	exec_default(char **cmd_args, t_smpl_cmd *pipe_argv, \
	t_node *env_list, char **env)
{
	char	*path;
	char	**my_directories;
	int		i;

	i = 0;
	path = get_variable(env_list, "PATH");
	if (!path)
		path = ft_strdup(cmd_args[0]);
	my_directories = ft_split(path, ':');
	lstclear(&env_list, delete_content);
	delete_cmd(pipe_argv);
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

void	exec_cmd(t_smpl_cmd *pipe_argv, t_node *env_list)
{
	char	**cmd_args;
	char	**env;

	check_built(pipe_argv);
	cmd_args = build_cmd_args(&pipe_argv->cmd_argv, pipe_argv->cmd_argc);
	env = get_env(env_list);
	if (cmd_args[0][0] == '.' && !cmd_args[0][1])
		exit_error("filename argument required", 2);
	if (cmd_args[0][0] == '/' || cmd_args[0][0] == '.')
	{
		check_cmd(cmd_args[0]);
		execve(cmd_args[0], cmd_args, env);
	}
	else
		exec_default(cmd_args, pipe_argv, env_list, env);
	ft_fprintf(2, "cc: ");
	perror("executor");
	exit(127); //heer
}

void	redirect(t_smpl_cmd *cmd, pid_t pid, int keep, int *fd_pipe)
{
	if (pid == 0)
	{
		if (set_fd(cmd, &keep, fd_pipe) == -1)
			exit_error("redirect", 1);
		close(fd_pipe[0]);
		dup2(keep, STDIN_FILENO);
		if (!keep)
			exit_error("dup fail", 1);
		if (!(!cmd->next && !set_fd(cmd, &keep, fd_pipe)))
			dup2(fd_pipe[1], STDOUT_FILENO);
		if (!fd_pipe[1])
			exit_error("dup fail", 1);
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

void	execute_child(t_smpl_cmd *temp)
{
	if (temp->cmd_argc > 0)
		exec_cmd(temp, temp->env_list);
	else
		execute_exit(NULL, temp->env_list);
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
			execute_child(temp);
		temp = temp->next;
		i++;
	}
	set_exit_st(pipeline->pipe_argc, pid);
}
