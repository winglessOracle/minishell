/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/12 11:37:06 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGTERM_H
# define SIGTERM_H

# include "minishell.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

void	handle_sigint(int signal_number);
void	set_signals(void);
void	set_sigint_here(void);
void	handle_sigint_here(int signal_number);
void	reset_terminal(void);

#endif
