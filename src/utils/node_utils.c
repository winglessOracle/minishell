/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 13:37:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/11 13:23:53 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(int type, char *content)
{
	t_node	*new_node;

	if (!content)
		exit_error(errno);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit_error(errno);
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	delete_content(void *content)
{
	char	*temp;

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

// merges provided node with the next node and set provided type for merged node
void	merge_tokens(t_node *token, int type)
{
	if (token->next)
	{
		token->content = ft_strjoin_free_s1(token->content, token->next->content);
		token->type = type;
		lstdelone(lstpop(&token->next), delete_content);
	}
}

t_node	*lstpop(t_node **lst)
{
	t_node	*temp;

	if (!*lst)
		return (NULL);
	temp = *lst;
	*lst = (*lst)->next;
	temp->next = NULL;
	return (temp);
}
