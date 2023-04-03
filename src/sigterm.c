/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/03 15:21:12 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "sigterm.h"

//swap ctrl-d (eof) and ctrl-c (sigint))
//https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal


//global variable for now
struct termios	old_termios;

void	set_sig_term()
{
	set_termios();
	set_signals();
}

void	handle_sigcont()
{
	set_termios();
}

void	handle_sigint()
{
	exit(EXIT_SUCCESS);
}

void	handle_sigquit()
{
	rl_replace_line("", 0);
	rl_on_new_line(); //not working as expected
	rl_redisplay();
}

void	set_signals()
{
	struct	sigaction sa_quit;
	struct	sigaction sa_cont;
	struct	sigaction sa_int;

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
//add more masks to signals?
    // VEOF: End-of-file character (usually ^D).
    // VERASE: Erase character (usually ^H).
    // VINTR: Interrupt character (usually ^C).
    // VKILL: Kill line character (usually ^U).
    // VSUSP: Suspend character (usually ^Z). (handeled in return)

//handle eof eof to create new line (char -1?) to create newline if buffer is filled of flusch buffer
void	set_termios()
{
	struct	termios	new_termios;
	// struct termios	old_termios;
	
	if (tcgetattr(STDIN_FILENO, &old_termios) == -1)
		exit(errno);
	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = old_termios.c_cc[VINTR];
	new_termios.c_cc[VINTR] = old_termios.c_cc[VEOF];
 	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios) == -1)
		exit(errno);
	if (atexit(restore_terminos) != 0)
		exit(errno);
}

void	restore_terminos()
{
	if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &old_termios) == -1)
		exit(errno);
}
