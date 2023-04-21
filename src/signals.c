/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/21 15:10:11 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "sigterm.h"

void	set_sig_term(void)
{
	set_termios();
	set_signals();
}
//turn off echo of for ctrl
void	handle_sigquit(int signal_number)
{
	(void) signal_number;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int signal_number)
{
	(void) signal_number;
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	unlink(TMP_FILE);
	exit(EXIT_SUCCESS);
}

void	set_signals(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_stop;
	struct sigaction	sa_int;

	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaddset(&sa_int.sa_mask, SIGINT);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		exit(errno);

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		exit(errno);

	sa_stop.sa_handler = SIG_IGN;
	sigemptyset(&sa_stop.sa_mask);
	sigaddset(&sa_stop.sa_mask, SIGTSTP);
	if (sigaction(SIGTSTP, &sa_stop, NULL) == -1)
		exit(errno);
}
