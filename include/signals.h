/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/17 10:14:29 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <signal.h>
# include <sys/wait.h>

void	handle_sigint_here(int signal_number);
void	handle_sigint(int signal_number);
void	handle_sigquit(int signal_number);
void	set_signals(void);

#endif
