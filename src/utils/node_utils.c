/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 13:37:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/09 11:52:10 by cariencaljo   ########   odam.nl         */
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
	new_node->prev = NULL;
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

// merges provided node with the next node and set provided type for merged node
void	merge_tokens(t_node *token, int type)
{
	char	*content;

	if (token->next)
	{
		content = ft_strjoin(token->content, token->next->content);
		free(token->content);
		token->content = content;
		token->type = type;
		token = token->next;
		lstdelone(lstpop(&token), delete_content);
	}
}

t_node	*lstpop(t_node **lst)
{
	t_node	*temp;

	if (!*lst)
		return (NULL);
	temp = *lst;
	if ((*lst)->prev)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->next;
	temp->prev = NULL;
	temp->next = NULL;
	return (temp);
}
