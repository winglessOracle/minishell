/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/21 14:37:22 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*get_next_cmd(t_node *tokens)
{
	t_node	*cmd;

	cmd = new_node(0, NULL);
	
}

void	parser(t_master *command_struct, t_node *tokens)
{
	t_node	*cmd;

	while (tokens)
	{
		cmd = get_next_cmd(tokens);
		if (cmd)
			lstadd_back(command_struct->commands, cmd);
	}
}