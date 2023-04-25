/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_pipe.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/25 11:59:48 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*lstlast_pipe(t_pipe *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_pipe(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (new)
	{
		temp = lstlast_pipe(*lst);
		if (temp)
			temp->next = new;
		else
			*lst = new;
	}
}

void	lstdelone_pipe(t_pipe *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del((void *)lst);
		free(lst);
	}
}

void	lstclear_pipelst(t_pipe **lst, void (*del)(void *))
{
	t_pipe	*temp;

	if (del && lst)
	{
		while (lst && *lst)
		{
			temp = (*lst)->next;
			lstdelone_pipe(*lst, del);
			*lst = temp;
		}
	}
}

int	remove_pipe_node(t_pipe **pipes)
{
	t_pipe	*temp;

	if (!*pipes)
		return (-1); //check
	temp = *pipes;
	*pipes = (*pipes)->next;
	temp->next = NULL;
	lstdelone_pipe(temp, delete_pipe);
	return (0);
}