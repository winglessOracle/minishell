/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/26 19:27:33 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	exec_cmd(t_smpl_cmd *pipe_argv, t_node *env_list)
{
	char	**my_directories;
	char	**cmd_args;
	char	**env;
	char	*path;
	int		i;

	i = 0;
	check_built(pipe_argv);
	cmd_args = build_cmd_args(&pipe_argv->cmd_argv, pipe_argv->cmd_argc);
	if (!cmd_args)
		exit_error("building commands", 1);
	env = get_env(env_list);
	// check for env = NULL?
	path = get_variable(env_list, "PATH");
	if (!path)
		path = ft_strdup(cmd_args[0]);
	my_directories = ft_split(path, ':');
	// check on fail for split?
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
	execve(cmd_args[0], cmd_args, env);
	exit_error("unknown command", 127);
}

void	assignments(t_smpl_cmd *pipe_argv, pid_t pid)
{
	t_node *temp;

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

int	set_fd(t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = smpl_cmd->redirect;
	while (temp)
	{
		if (temp->type == OUTPUT)
		{
			if (access(temp->content, F_OK) == 0)
				return (return_error("not allowed to overwrite file\n", -1));
			fd_pipe[1] = open(temp->content, \
								O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd_pipe[1] < 0)
				return (return_perror("opening outfile", -1));
			count = 1;
		}
		else if (temp->type == INPUT)
		{
			close(*keep);
			*keep = open(temp->content, O_RDONLY);
			if (*keep < 0)
				return (return_perror("opening keep", -1));
		}
		else if (temp->type == APPEND)
		{
			close(fd_pipe[1]);
			fd_pipe[1] = open(temp->content, \
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd_pipe[1] < 0)
				return (return_perror("opening outfile", -1));
			count = 1;
		}
		else if (temp->type == HEREDOC || temp->type == HEREDOCQ)
		{
			dup2(smpl_cmd->here_doc, *keep);
			if (!smpl_cmd->here_doc)
				exit_error("dup fail", -1);
		}
		if (*keep == -1 || fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (return_perror("fd:", -1));
		temp = temp->next;
	}
	return (count);
}

void	redirect(t_smpl_cmd *cmd, pid_t pid, int keep, int *fd_pipe)
{
	int		set_out;

	if (pid == 0)
	{
		close(fd_pipe[0]);
		set_out = set_fd(cmd, &keep, fd_pipe);
		if (set_out == -1)
			exit_error("ccs: redirect\n", 12); //change
		dup2(keep, STDIN_FILENO);
		if (!keep)
			exit_error("dup fail", 1); //change
		if (!(!cmd->next && !set_out))
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

void		executor(t_pipe *pipeline)
{
	pid_t		pid[pipeline->pipe_argc];
	int			fd_pipe[2];
	int			keep;
	int			i;
	t_smpl_cmd	*cmd;
	
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
		if (pid[i] == 0)
		{
			if (cmd->cmd_argc > 0)
				exec_cmd(cmd, cmd->env_list);
			else
				execute_exit(NULL, cmd->env_list);
		}
		cmd = cmd->next;
		i++;
	}
	set_exit_st(pipeline->pipe_argc, pid);
}
