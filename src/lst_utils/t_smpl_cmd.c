/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_smpl_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/20 16:45:53 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_smpl_cmd	*lstlast_cmd(t_smpl_cmd *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_cmd(t_smpl_cmd **lst, t_smpl_cmd *new)
{
	t_smpl_cmd	*temp;

	if (new)
	{
		temp = lstlast_cmd(*lst);
		if (temp)
			temp->next = new;
		else
			*lst = new;
	}
}

void	lstdelone_cmd(t_smpl_cmd *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del((void *)lst);
		free(lst);
	}
}

void	lstclear_cmdlst(t_smpl_cmd **lst, void (*del)(void *))
{
	t_smpl_cmd	*temp;

	if (del && lst)
	{
		while (lst && *lst)
		{
			temp = (*lst)->next;
			lstdelone_cmd(*lst, del);
			*lst = temp;
		}
	}
}

int	remove_cmd_node(t_smpl_cmd **cmds)
{
	t_smpl_cmd	*temp;
	if (!*cmds)
		return (-1); //check
	temp = *cmds;
	*cmds = (*cmds)->next;
	temp->next = NULL;
	lstdelone_cmd(temp, delete_cmd);
	printf("removed cmd_node\n");
	return (0);
}