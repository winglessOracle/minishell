/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:49:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 17:13:27 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_cmd(t_node *token, t_smpl_cmd *cmd)
{
	int	check;
	
	if (cmd->cmd_argc == 0 && cmd->errfile == 0 && cmd->infile == 0 \
		&& cmd->outfile == 0 && cmd->here_end == 0)
		check = -1;
	else
		check = 1;
	if (check == -1)
		write(2, "Error: syntax error near unexpected token 'x'\n", 46); //include ft_fprintf for better error messages and create seperate funtion that writes the error		
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
