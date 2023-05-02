/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/02 09:48:49 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		exit_error("ccs: No such file or directory\n", 127);
	else if (access(cmd, X_OK) == -1)
		exit_error("ccs: Permission denied\n", 126);
	return ;
}

int	exec_relative(char *cmd_args, t_node *env_list, char **env)
{
	char	*pwd;
	char	buf[PATH_MAX];
	char	*new_dir;

	pwd = get_variable(env_list, "PWD");
	if (!pwd)
	{
		getcwd(buf, PATH_MAX);
		pwd = ft_strdup(buf);
	}
	if (!pwd)
		return (-1);
	new_dir = new_directory(cmd_args, pwd);
	check_cmd(new_dir);
	return (execve(new_dir, &cmd_args, env));
}

int	exec_default(char **cmd_args, t_smpl_cmd *pipe_argv, t_node *env_list, char **env)
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
	if (cmd_args[0][0] == '/')
	{
		check_cmd(cmd_args[0]);
		execve(cmd_args[0], cmd_args, env);
	}
	else if (cmd_args[0][0] == '.')
		exec_relative(cmd_args[0], env_list, env);
	else
		exec_default(cmd_args, pipe_argv, env_list, env);
	exit_error("ccs: command not found\n", 127);
}

void	assignments(t_smpl_cmd *pipe_argv, pid_t pid)
{
	t_node	*temp;

	temp = pipe_argv->assign;
	if (pid == 0)
	{
		while (temp)
		{
			add_variable(pipe_argv->env_list, \
						ft_strdup(temp->content), 1); //moet dit niet 2 zijn?
			temp = temp->next;
		}
	}
}

int		set_out(int *fd_pipe, t_node *temp)
{
	if (temp->type == OUTPUT)
		fd_pipe[1] = open(temp->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp->type == APPEND)
		fd_pipe[1] = open(temp->content, O_CREAT | O_WRONLY | O_APPEND, 0644);	
	return (1);
}

void	set_in(int keep, t_node *temp)
{
	close (keep);
	keep = open(temp->content, O_RDONLY);
}

/*
Redirects to exisiting files in MacOs are not allowed default. 
In other Linus systems this is not the case. We choose to take
the Linux approach and allow overwriting existing files.
To modify the behaviour in bash to meet our version change the
noclobber setting: 'set +o noclobber'.*/
int	set_fd(t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = smpl_cmd->redirect;
	while (temp)
	{
		if (temp->type == OUTPUT || temp->type == APPEND)
			count = set_out(fd_pipe, temp);
		else if (temp->type == INPUT)
			set_in(*keep, temp);
		else if (temp->type == HEREDOC || temp->type == HEREDOCQ)
		{
			dup2(smpl_cmd->here_doc, *keep);
			if (!smpl_cmd->here_doc)
				exit_error("dup fail", -1);
		}
		if (*keep == -1 || fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (return_perror("setting file descriptor", -1));
		temp = temp->next;
	}
	return (count);
}

void	redirect(t_smpl_cmd *cmd, pid_t pid, int keep, int *fd_pipe)
{
	if (pid == 0)
	{
		close(fd_pipe[0]);
		if (set_fd(cmd, &keep, fd_pipe) == -1)
			exit_error("ccs: redirect\n", 12); //change
		dup2(keep, STDIN_FILENO);
		if (!keep)
			exit_error("dup fail", 1); //change
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

void	read_heredocs(t_pipe *pipeline)
{
	t_smpl_cmd	*tcmd;
	t_node		*tredirect;

	tcmd = pipeline->pipe_argv;
	while (tcmd)
	{
		tredirect = tcmd->redirect;
		while (tredirect)
		{
			if (tredirect->type == HEREDOC || tredirect->type == HEREDOC)
			{
				if (tcmd->here_doc)
					close(tcmd->here_doc);
				tcmd->here_doc = here_doc(pipeline, tredirect);
			}
			tredirect = tredirect->next;
		}
		tcmd = tcmd->next;
	}
}

// void	exec_child(pid_t pid, t_smpl_cmd *cmd, int keep, int fd_pipe[2])
// {
// 	char	buffer[128];

// 	if (pid == 0)
// 	{
// 		if (cmd->cmd_argc > 0)
// 			exec_cmd(cmd, cmd->env_list);
// 		else
// 		{
// 			while (read(keep, buffer, 128 ))
// 				printf("%.128s", buffer);
// 			close (keep);
// 			close (fd_pipe[1]);
// 			execute_exit(NULL, cmd->env_list);
// 		}
// 	}
// }

void		executor(t_pipe *pipeline)
{
	pid_t		pid[pipeline->pipe_argc];
	int			fd_pipe[2];
	int			keep;
	int			i;
	t_smpl_cmd	*cmd;
	char		buffer[128];

	cmd = pipeline->pipe_argv;
	if (!pipeline)
		return ;
	i = 0;
	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
	read_heredocs(pipeline);
	while (pipeline && cmd)
	{
		if (pipeline->pipe_argc == 1)
		{
			if (cmd->cmd_argc == 0)
				assignments(cmd, 0);
			if (check_builtins_curr_env(cmd))
				break ;
		}
		if (pipe(fd_pipe) == -1)
			exit_error("pipe fail", errno);
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("fork fail", errno);
		redirect(cmd, pid[i], keep, fd_pipe);
		assignments(cmd, pid[i]);
		// exec_child(pid[i], cmd, keep, fd_pipe);
		if (pid[i] == 0)
		{
			if (cmd->cmd_argc > 0)
				exec_cmd(cmd, cmd->env_list);
			else
			{
				while (read(keep, buffer, 128 ))
					printf("%.128s", buffer);
				close (keep);
				close (fd_pipe[1]);
				execute_exit(NULL, cmd->env_list);
			}
		}
		cmd = cmd->next;
		i++;
	}
	set_exit_st(pipeline->pipe_argc, pid);
}

