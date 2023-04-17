/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:37:37 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/17 20:08:15 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	The exit utility shall cause the shell to exit from its current
       execution environment with the exit status specified by the
       unsigned decimal integer n.  If the current execution environment
       is a subshell environment, the shell shall exit from the subshell
       environment with the specified exit status and continue in the
       environment from which that subshell environment was invoked;
       otherwise, the shell utility shall terminate with the specified
       exit status. If n is specified, but its value is not between 0
       and 255 inclusively, the exit status is undefined.

       A trap on EXIT shall be executed before the shell terminates,
       except when the exit utility is invoked in that trap itself, in
       which case the shell shall exit immediately.*/

void	execute_exit(char **cmd_vector, t_node *env_list)
{
	int	exit_code;

	(void)env_list;
	if (cmd_vector[1] != NULL)
		exit_code = ft_atoi_long(cmd_vector[1]);
	else
		exit(EXIT_SUCCESS);
}
