/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/03 15:42:25 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");
}

//add cwd later
void	init_variables(t_node *env_list)
{
	char	*prompt;

	prompt = "PS1=\033[34;1mCC|$HELL$ \033[0m";
	add_variable(env_list, prompt, 1);
	add_variable(env_list, "PS2=''", 1);
}
