/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/09 11:38:26 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*lstlast(t_node *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int	lstlen(t_node *lst)
// {
// 	int	i;
	
// 	i = 0;
// 	while (lst && lst->next != NULL)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }

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

void	lstinsert_lst(t_node **at, t_node *lst)
{
	t_node	*temp;
	t_node	*last;
	
	if (!lst)
		return ;
	if (*at == NULL)
	{
		*at = lst;
		return ;
	}
	temp = *at;
	last = lstlast(lst);
	last->next = temp;
	*at = lst;
	if (temp->prev)
		temp->prev->next = lst;
}
