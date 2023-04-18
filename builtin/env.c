/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 12:30:26 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/18 12:49:00 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(char **cmd_vector, t_node	*env_list)
{
	int	i;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 1)
		return (return_error("env: No such file or directory\n", 127));
	print_env(env_list, 2);
	return (0);
}