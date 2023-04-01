/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigterm.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 21:32:23 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/01 21:39:23 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include <signal.h>
# include <termios.h>

void	set_sig_term();
void	handle_sigcont();
void	set_signals();
void	set_termios();
void	restore_terminos();
