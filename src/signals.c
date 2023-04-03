/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/03 16:40:42 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sigterm.h"

void	set_sig_term(void)
{
	set_termios();
	set_signals();
}

void	handle_sigcont(int signal_number)
{
	(void) signal_number;
	set_termios();
}

void	handle_sigint(int signal_number)
{
	(void) signal_number;
	exit(EXIT_SUCCESS);
}

void	handle_sigquit(int signal_number)
{
	(void) signal_number;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line(); //not working as expected
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_cont;
	struct sigaction	sa_int;

	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		exit(errno);
	sa_cont.sa_handler = handle_sigcont;
	sa_cont.sa_flags = 0;
	if (sigaction(SIGCONT, &sa_cont, NULL) == -1)
		exit(errno);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		exit(errno);
}
