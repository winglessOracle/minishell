/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/08 19:18:51 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGTERM_H
# define SIGTERM_H

# include "minishell.h"
# include <signal.h>
//# include <termios.h>

void	handle_sigcont(int signal_number);
void	handle_sigint(int signal_number);
void	handle_sigquit(int signal_number);
void	set_signals(void);
void	set_sigint_here(void);
void	handle_sigint_here(int signal_number);

#endif
