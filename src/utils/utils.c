/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/06 11:45:42 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int num)
{
	write(1, "Error\n", 7);
	exit(num);
}

// to be used in executer
int assign(t_node **token, t_smpl_cmd *cmd)
{
	// in fork when commands has arguments. else in current env
	add_variable(cmd->env_list, (*token)->content, 1);
	remove_node(token, cmd);
	return (0);
}

int	syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg)
{
	(void)token;
	(void)cmd;
	write(2, msg, ft_strlen(msg));
	// clear tokens up to next newline or ;
	// clear current command and previous commands in pipeline
	return (-1);
}