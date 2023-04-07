/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/07 14:32:31 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int num)
{
	write(1, "Error\n", 7);
	exit(num);
}

// to be used in executer
int	assign(t_node **token, t_smpl_cmd *cmd)
{
	// in fork when commands has arguments. else in current env
	add_variable(cmd->env_list, (*token)->content, 1);
	remove_node(token, cmd);
	return (0);
}

// prints error message and returns -1 if err != 0;
int	syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg, int err)
{
	if (err != 0)
	{
		write(2, msg, ft_strlen(msg));
		while (*token && (*token)->type != NEW_LINE)  // add ;?
			remove_node(token, cmd);
		while (cmd && cmd->prev)
			cmd = cmd->prev;
		lstclear_pipe(&cmd, delete_cmd);
		cmd = NULL;
		return (-1);
	}
	else
		return (0);
}
