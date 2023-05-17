/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 16:04:23 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/16 09:47:39 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

void	fork_error(void)
{
	kill(getpid(), SIGINT);
	return_error ("fork: resource temporarily unavailable", 1, 128);
	return ;
}

int	init_keep(void)
{
	int	keep;

	keep = dup(STDIN_FILENO);
	if (!keep)
		exit_error("dup fail", 1);
	return (keep);
}

pid_t	*init_pid(int argc)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * (argc + 1));
	if (!pid)
		exit_error("malloc error", 2);
	ft_memset(pid, 0, sizeof(pid_t));
	return (pid);
}
