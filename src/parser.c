/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/28 19:29:53 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// if LESS || GREAT -> check next and set redirect
// if PIPE or NEW_LINE -> end simple command?
// else -> skip

// other:
//  done: if # (at start of token) -> replace # with '\0' and remove all next tokens until (but excluding) next '\n' 
//  done: if " -> find closing " 
//  done: if ' -> find closing '
// if $ -> expand to (env)value
// if $?	-> expand to last exit status

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
		else if (*str == 61 && state == 0)
			state = ASSIGN;
		str++;
	}
	return (state);
}
