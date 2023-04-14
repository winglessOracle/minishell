/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/13 22:00:50 by cariencaljo   ########   odam.nl         */
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
	printf("cmd_arg[0]=%s\n", cmd_args[0]); //remove
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
//	execve(cmd_args[0], cmd_args, env); //kan weg denk ik
	exit(EXIT_FAILURE);
}

void	assignments(t_smpl_cmd *pipe_argv, pid_t pid, t_node *env_list)
{
	if (pipe_argv->next)
	{
		if (pid == 0)
		{
			while (pipe_argv->assign)
			{
				add_variable(pipe_argv->env_list, pipe_argv->assign->content, 1);
			//	lstdelone(lstpop(&pipe_argv->assign), delete_content);
				pipe_argv->assign = pipe_argv->assign->next;
			}
		}
	}
	else
	{
		if (pid != 0)
		{
			while (pipe_argv->assign)
			{
				add_variable(env_list, pipe_argv->assign->content, 1);
			//	lstdelone(lstpop(&pipe_argv->assign), delete_content);
				pipe_argv->assign = pipe_argv->assign->next;
			}
		}	
	}
	//clearlist?
}

int	set_fd(t_pipe *pipeline, t_smpl_cmd *smpl_cmd)
{
	while(smpl_cmd->redirect)
	{
		if (smpl_cmd->redirect->type == INPUT)
			pipeline->fd_pipe[0] = open(smpl_cmd->redirect->content, O_RDONLY);
		else if (smpl_cmd->redirect->type == OUTPUT)
			pipeline->fd_pipe[1] = open(smpl_cmd->redirect->content, O_WRONLY);
		else if (smpl_cmd->redirect->type == APPEND)
			pipeline->fd_pipe[1] = open(pipeline->pipe_argv->redirect->content, O_APPEND);
//		else if (pipe->redirect->type == HEREDOC)
		if (pipeline->fd_pipe[0] == -1 || pipeline->fd_pipe[1] == -1)
			return (-1);
		remove_node(&smpl_cmd->redirect, NULL);
	}
	return (0);
}

void	redirect(t_pipe *pipeline, pid_t pid)
{
	if (pid == 0)
	{
		close(pipeline->fd_pipe[0]);
		// if (set_fd(pipeline, pipeline->pipe_argv) != 0)
		// 	perror("No such file or directory\n");
		dup2(pipeline->fd_pipe[1], STDOUT_FILENO);
		dup2(pipeline->fd_keep, STDIN_FILENO);

		printf("\n\tTEST in child\n");
	}
	else
	{
		close(pipeline->fd_keep);
		pipeline->fd_keep = dup(pipeline->fd_pipe[0]);
		close(pipeline->fd_pipe[0]);
		close(pipeline->fd_pipe[1]);
	
		printf("\n\tTEST in parent\n");
	}
}

int		executor(t_pipe *pipeline)
{
	int			exitstatus;
 	pid_t		pid;
	char		**env;

	exitstatus = 0;
 	while (pipeline && pipeline->pipe_argv)
	{
	 	if (pipe(pipeline->fd_pipe) == -1)
	 		exit_error("pipe fail", errno);
	 	env = get_env(pipeline->pipe_argv->env_list);
		pid = fork();
	 	if (pid == -1)
			exit_error("fork fail", errno);
		// redirect(pipeline, pid);
		//assignments(pipeline->pipe_argv, pid, env_list);
		if (pid == 0)
		{
			// printf("in child\n");
		 	exec_cmd(pipeline->pipe_argv, env);
		}
		// //lstclear(&pipeline->pipe_argv->env_list, delete_content);
	 	// else
		pipeline->pipe_argv = pipeline->pipe_argv->next;
	// 	free (env);
	}
	// exitstatus = get_exit_st(pipeline->pipe_argv, pid);
	return (exitstatus);
	// clean lists 
	// close pipes
}

// eerst oplossen exec en assig en dan redfirect lezen std in en out
// only use local env