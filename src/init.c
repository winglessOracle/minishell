/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/03 17:04:32 by cwesseli      ########   odam.nl         */
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

	prompt = "PS1=\x1b[0;36mCC|$HELL \033[0m";
	add_variable(env_list, prompt, 1);
	add_variable(env_list, "PS2=''", 1);
}
