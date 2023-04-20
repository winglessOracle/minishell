/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 13:37:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/20 19:13:18 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(int type, char *content)
{
	t_node	*new_node;

	if (!content)
		exit_error("no content for new node", errno);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit_error("new_node", errno);
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// merges provided node with the next node and set provided type for merged node
void	merge_tokens(t_node *token, int type)
{
	if (token->next)
	{
		if (!token->content)
			token->content = token->next->content;
		else if (token->next->content)
			token->content = ft_strjoin_free_s1(token->content, \
										token->next->content);
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

int	remove_node(t_node **token, t_smpl_cmd *cmd)
{	
	t_node	*temp;
	int		state;

	(void)cmd;
	state = 0;
	if (!*token)
		return (-1);
	if ((*token)->type == NEW_LINE)
		state = 1;
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (state);
}
