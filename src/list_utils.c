/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/24 09:23:33 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(int type, void *content)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(errno);						//create exit error function?
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_node	*lstlast(t_node *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_node **lst, t_node *new)
{
	t_node	*temp;

	if (new)
	{
		temp = lstlast(*lst);
		if (temp)
		{
			temp->next = new;
			new->prev = temp;
		}
		else
			*lst = new;
	}
}

void	lstdelone(t_node *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del((void *)lst->content);
		free(lst);
	}
}

void	lstclear(t_node **lst, void (*del)(void *))
{
	t_node	*temp;

	if (del && lst)
	{
		while (lst && *lst)
		{
			temp = (*lst)->next;
			lstdelone(*lst, del);
			*lst = temp;
		}
	}
}