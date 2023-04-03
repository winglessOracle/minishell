/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termios.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 15:52:32 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/03 15:52:35 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sigterm.h"

//swap ctrl-d (eof) and ctrl-c (sigint))
//https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal

//global variable for now
//struct termios	old_termios;

// add more masks to signals?
// VEOF: End-of-file character (usually ^D).
// VERASE: Erase character (usually ^H).
// VINTR: Interrupt character (usually ^C).
// VKILL: Kill line character (usually ^U).
// VSUSP: Suspend character (usually ^Z). (handeled in return)
// handle eof eof to create new line (char -1?) to create newline 
//if buffer is filled of flusch buffer

void	set_termios(void)
{
	struct termios	new_termios;
	struct termios	old_termios;

	if (tcgetattr(STDIN_FILENO, &old_termios) == -1)
		exit(errno);
	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = old_termios.c_cc[VINTR];
	new_termios.c_cc[VINTR] = old_termios.c_cc[VEOF];
 	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios) == -1)
		exit(errno);
	// if (atexit(restore_terminos) != 0)
	// 	exit(errno);
}

// void	restore_terminos()
// {
// 	if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &old_termios) == -1)
// 		exit(errno);
// }