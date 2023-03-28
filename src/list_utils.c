/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/28 19:04:39 by cariencaljo   ########   odam.nl         */
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

// void	lstadd_front(t_node **lst, t_node *new)
// {
// 	t_node	**temp;

// 	if (new)
// 	{
// 		temp = lst;
// 		new->next = *temp;
// 		*lst = new;
// 	}
// }

void	delete_content(void *content)
{
	char	*temp;
	
	temp = (char *)content;
	free(temp);
}

void	lstdelone(t_node *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del((void *)lst->content);
		free(lst);
	}
}

t_node	*lst_pop(t_node **lst)
{
	t_node	*temp;

	temp = *lst;
	*lst = (*lst)->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
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

// void	lstswapt_last(t_node **lst)
// {
// 	t_node *last;
// 	t_node *second_last;

// 	if (lst && *lst && (*lst)->next)
// 	{
// 		last = lstlast(*lst);
// 		second_last = last->prev;
// 		last->prev = second_last->prev;
// 		last->next = second_last;
// 		second_last->prev->next = last;
// 		second_last->prev = last;
// 		second_last->next = NULL;		
// 	}
// }

// void	lstadd_secondback(t_node **lst, t_node *new)
// {
// 	t_node	*temp;

// 	if (new)
// 	{
// 		if (*lst == NULL)
// 			*lst = new;
// 		else if ((*lst)->next == NULL)
// 		{
// 			(*lst)->prev = new;
// 			new->next = *lst;
// 			*lst = new;
// 		}
// 		else
// 		{
// 			temp = *lst;
// 			while (temp->next->next != NULL)
// 				temp = temp->next;
// 			new->next = temp->next;
// 			temp->next->prev = new;
// 			temp->next = new;
// 			new->prev = temp;
// 		}
// 	}
// }
