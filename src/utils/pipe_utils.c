/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 12:53:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_pipe(t_node *token, t_smpl_cmd *cmd)
{
	int	check;
	
	if (token->type == PIPE && !token->next)
	{
		write(2, "Error: no command after '|'\n", 28); //include ft_fprintf for better error messages and create seperate funtion that writes the error
		check = -1;
	}
	else if (cmd->cmd_argv == 0 && cmd->redirect == NULL)
	{
		
		write(2, "Error: '|' at start of line\n", 28); //include ft_fprintf for better error messages and create seperate funtion that writes the error		
		check = -1;
	}
	else
		check = 1;
	return (check);
}

t_smpl_cmd	*lstlast_pipe(t_smpl_cmd *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_pipe(t_smpl_cmd **lst, t_smpl_cmd *new)
{
	t_smpl_cmd	*temp;

	if (new)
	{
		temp = lstlast_pipe(*lst);
		if (temp)
			temp->next = new;
		else
			*lst = new;
	}
}

// void	delete_cmd(void *smpl_cmd)
// {
// 	t_smpl_cmd	*temp;

// 	temp = (t_smpl_cmd *)smpl_cmd;
// 	lstclear(temp, delete_content);
// }

// void	lstdelone_pipe(t_smpl_cmd *lst, void (*del)(void *))
// {
// 	if (lst && del)
// 	{
// 		del((void *)lst->pipe_argv);
// 		free(lst);
// 	}
// }

// void	lstclear_pipe(t_smpl_cmd **lst, void (*del)(void *))
// {
// 	t_smpl_cmd	*temp;

// 	if (del && lst)
// 	{
// 		while (lst && *lst)
// 		{
// 			temp = (*lst)->next;
// 			lstdelone_pipe(*lst, del);
// 			*lst = temp;
// 		}
// 	}
// }
