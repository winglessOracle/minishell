/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_set.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/11 18:31:25 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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

int	set_out(int *fd_pipe, t_node *temp)
{
	if (temp->type == OUTPUT)
		fd_pipe[1] = open(temp->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp->type == APPEND)
		fd_pipe[1] = open(temp->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (1);
}

void	set_in(int *keep, t_node *temp)
{
	close (*keep);
	*keep = open(temp->content, O_RDONLY);
}

/*
Redirects to exisiting files in MacOs are not allowed default. 
In other Linus systems this is not the case. We choose to take
the Linux approach and allow overwriting existing files.
To modify the behaviour in bash to meet our version change the
noclobber setting: 'set +o noclobber'.*/
int	set_fd(t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe)
{
	int		trigger;
	t_node	*temp;

	trigger = 0;
	temp = smpl_cmd->redirect;
	while (temp)
	{
		if (temp->type == OUTPUT || temp->type == APPEND)
			trigger = set_out(fd_pipe, temp);
		else if (temp->type == INPUT)
			set_in(keep, temp);
		else if (temp->type == HEREDOC || temp->type == HEREDOCQ)
		{
			dup2(smpl_cmd->here_doc, *keep);
			if (!smpl_cmd->here_doc)
				exit_error("dup fail", -1);
		}
		if (*keep == -1 || fd_pipe[0] == -1 || fd_pipe[1] == -1)
			return (-1);
		temp = temp->next;
	}
	return (trigger);
}

int	assign_one(t_pipe *pipeline)
{
	if (pipeline->pipe_argv->cmd_argc == 0)
		assignments(pipeline->pipe_argv, 0);
	if (check_builtins_curr_env(pipeline->pipe_argv))
		return (1);
	return (0);
}
