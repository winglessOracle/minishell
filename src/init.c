/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/01 22:00:04 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");	
}

void	init_variables(t_node *env_list)
{
	char	*prompt;
	//add cwd later
	prompt = "PS1=\033[34;1mCC_SHELL$_\033[0m";
	add_variable(env_list, prompt, 1);
	add_variable(env_list, "PS2=''", 1);
}
