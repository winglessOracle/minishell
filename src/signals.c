/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/01 21:39:20 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "sigterm.h"

//swap ctrl-d (eof) and ctrl-c (sigint))
//https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal

void	set_sig_term()
{
	set_termios();
	set_signals();
}

void	handle_sigcont()
{
	set_termios();
}

void	set_signals()
{
	struct	sigaction sa_quit;
	struct	sigaction sa_cont;

	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	 	exit(errno);
	sa_cont.sa_handler = handle_sigcont;
	sa_cont.sa_flags = 0;
}

void	set_termios()
{
	struct	termios old_termios;
	struct	termios	new_termios;
	
	if (tcgetattr(STDIN_FILENO, &old_termios) == -1)
		exit(errno);
	new_termios = old_termios;
	new_termios.c_cc[VEOF] = old_termios.c_cc[VINTR];
	new_termios.c_cc[VINTR] = old_termios.c_cc[VEOF];
	// new_termios.c_cc[VEOF] = old_termios.c_cc[VEOF];
	// new_termios.c_cc[VINTR] = old_termios.c_cc[VINTR];
	if (tcsetattr(STDIN_FILENO, 0, &new_termios) == -1)
		exit(errno);
	signal(SIGCONT, handle_sigcont);

	if (atexit(restore_terminos) != 0)
		exit(errno);
}

void	restore_terminos()
{
	struct	termios temp_termios;

	if (tcgetattr(STDIN_FILENO, &temp_termios) == -1)
		exit(errno);
	if (tcsetattr(STDERR_FILENO, 0, &temp_termios) == -1)
		exit(errno);
}
