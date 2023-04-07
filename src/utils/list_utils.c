/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/06 22:28:42 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
