/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/11 10:52:43 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGTERM_H
# define SIGTERM_H

# include "minishell.h"
# include <signal.h>
# include <termios.h>

void	set_sig_term(void);
void	handle_sigcont(int signal_number); // niet gebruikt?
void	handle_sigint(int signal_number);
void	handle_sigquit(int signal_number);
void	set_signals(void);
void	set_termios(void);
void	restore_terminos(void);

#endif
