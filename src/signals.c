/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/31 19:08:26 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	handler_sigint(int num)
{
	//printf("SIGINT not allowed\n"); //remove later
	rl_on_new_line();
}

void	set_signals()
{
	struct sigaction act;
	
	act.sa_handler = &handler_sigint;
	if (sigaction(SIGINT, &act, NULL) == -1)
		exit(errno);
}
	// 3x handeled?
	// masks? for al
	//raise?;