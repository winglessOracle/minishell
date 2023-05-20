/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 14:53:32 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/19 09:59:12 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_content(void *content)
{
	char	*temp;

	if (!content)
		return ;
	temp = (char *)content;
	free(temp);
}

void	delete_cmd(void *smpl_cmd)
{
	t_smpl_cmd	*cmd;

	cmd = (t_smpl_cmd *)smpl_cmd;
	lstclear(&cmd->redirect, delete_content);
	lstclear(&cmd->assign, delete_content);
	lstclear(&cmd->cmd_argv, delete_content);
}

void	delete_pipe(void *pipe)
{
	t_pipe	*pipeline;

	pipeline = (t_pipe *)pipe;
	lstclear_cmdlst(&pipeline->pipe_argv, delete_cmd);
	free(pipe);
}
