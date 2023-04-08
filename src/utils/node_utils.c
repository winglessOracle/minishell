/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 13:37:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/08 20:51:42 by cariencaljo   ########   odam.nl         */
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

int	remove_node(t_node **token, t_smpl_cmd *cmd)
{	
	t_node	*temp;

	(void)cmd;
	if (!*token)
		return (-1);
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (0);
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