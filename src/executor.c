/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/14 16:09:54 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

void	exec_cmd(t_smpl_cmd *pipe_argv, char **env)
{
	char	**my_directories;
	char	**cmd_args;
	char	*path;
	int		i;

	i = 0;
	cmd_args = build_cmd_args(pipe_argv->cmd_argv, pipe_argv->cmd_argc);
	if (!cmd_args)
		exit(EXIT_FAILURE);
	path = get_variable(pipe_argv->env_list, "PATH");
	if (!path)
	{
		execve(cmd_args[0], cmd_args, env);
		exit(EXIT_FAILURE);
	}
	my_directories = ft_split(path, ':');
	free(path);
	while (my_directories[i])
	{
		path = ft_strjoin(my_directories[i], "/");
		path = ft_strjoin_free_s1(path, cmd_args[0]);
		execve(path, cmd_args, env);
		ft_free(path);
		i++;
	}
	ft_free(my_directories);
	exit_error("cmd not found", 1);
//	execve(cmd_args[0], cmd_args, env); //kan weg denk ik
	// exit(EXIT_FAILURE);
}

// void	assignments(t_smpl_cmd *pipe_argv, pid_t pid, t_node *env_list)
// {
// 	if (pipe_argv->next)
// 	{
// 		if (pid == 0)
// 		{
// 			while (pipe_argv->assign)
// 			{
// 				add_variable(pipe_argv->env_list, pipe_argv->assign->content, 1);
// 			//	lstdelone(lstpop(&pipe_argv->assign), delete_content);
// 				pipe_argv->assign = pipe_argv->assign->next;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (pid != 0)
// 		{
// 			while (pipe_argv->assign)
// 			{
// 				add_variable(env_list, pipe_argv->assign->content, 1);
// 			//	lstdelone(lstpop(&pipe_argv->assign), delete_content);
// 				pipe_argv->assign = pipe_argv->assign->next;
// 			}
// 		}	
// 	}
// 	//clearlist?
// }

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
		// printf("cmd: %s, in: %d, out: %d\n", pipeline->pipe_argv->cmd_argv->content, fd_keep, fd_pipe[1]);
		// if (set_fd(pipeline, pipeline->pipe_argv, &fd_keep, fd_pipe) != 0)
		// 	perror("No such file or directory\n");
	}
	else
	{	
		// printf("keep: %d, pipe[0]: %d\n", keep, fd_pipe[0]);
		close(fd_keep);
		if (pipeline->pipe_argv->next)
			fd_keep = dup(fd_pipe[0]);
		// printf("redirected keep: %d\n", keep);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

int		executor(t_pipe *pipeline)
{
	int			exitstatus;
	int			keep;
	int			fd_pipe[2];
 	pid_t		pid;
	char		**env;

	exitstatus = 0;
	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
 	while (pipeline && pipeline->pipe_argv)
	{
	 	if (pipe(fd_pipe) == -1)
	 		exit_error("pipe fail", errno);
		// printf("keep: %d, pipe, [0]: %d, [1]: %d\n", keep, fd_pipe[0], fd_pipe[1]);
	 	env = get_env(pipeline->pipe_argv->env_list);
		pid = fork();
	 	if (pid == -1)
			exit_error("fork fail", errno);
		// assignments(pipeline->pipe_argv, pid, env_list);
		redirect(pipeline, pid, keep, fd_pipe);
		if (pid == 0)
		{
		 	exec_cmd(pipeline->pipe_argv, env);
		}
		else
			pipeline->pipe_argv = pipeline->pipe_argv->next;
		wait(NULL);
	}
	exitstatus = get_exit_st(pipeline->pipe_argv, pid);
	return (exitstatus);
	// 	free (env);
	// clean lists 
}

// eerst oplossen exec en assig en dan redfirect lezen std in en out
// only use local env