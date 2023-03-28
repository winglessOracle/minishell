/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/28 10:07:28 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	get_state(char *str)
{
	int		state;

	state = 0;
	if (*str == '#')
		return (COMMENT);
	while (*str)
	{
		if (*str == 34 && state == 0)
			state = D_QUOTE;
		else if (*str == 39 && state == 0)
			state = S_QUOTE;
		else if (*str == 34 && state == D_QUOTE)
			state = 0;
		else if (*str == 39 && state == S_QUOTE)
			state = 0;
		else if (*str == 36 && state != S_QUOTE)
			state = EXPAND;
		else if (*str == 61 && state != S_QUOTE && state != D_QUOTE)
			state = ASSIGN;
		str++;
	}
	return (state);
}

// meta:
// |, <, >, ' ', '\t, '\n'
// ignore  &, ;, (, ) for now

// if LESS || GREAT -> check next and set redirect
// if PIPE or NEW_LINE -> end simple command?
// else -> skip

//  other:
// done: if # (at start of token) -> replace # with '\0' and remove all next tokens until (but excluding) next '\n' 
// done: if " -> find closing " 
// done: if ' -> find closing '
// if $ -> expand to (env)value
// if $?	-> expand to last exit status


// t_node	*get_next_cmd(t_node *tokens)
// {
// 	t_node	*cmd;
// 	char	**cmd_vector;
// 	int		cmd_type;

// 	cmd_vector = NULL;
// 	cmd_type = 0;
// 	cmd = new_node(cmd_type, cmd_vector);
// 	return (cmd);
// }

// void	parser(t_master *command_struct, t_node *tokens)
// {
// 	t_node	*cmd;

// 	while (tokens)
// 	{
// 		cmd = get_next_cmd(tokens);
// 		if (cmd)
// 			lstadd_back(command_struct->commands, cmd);
// 	}
// }
	