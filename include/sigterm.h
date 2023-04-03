/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/03 15:58:32 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGTERM_H
# define SIGTERM_H

# include "minishell.h"
# include <signal.h>
# include <termios.h>

void	set_sig_term(void);
void	handle_sigcont(void);
void	handle_sigint(void);
void	handle_sigquit(void);
void	set_signals(void);
void	set_termios(void);
void	restore_terminos(void);

#endif
