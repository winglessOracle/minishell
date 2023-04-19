/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:37:37 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/18 11:22:57 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(char **cmd_vector, t_node *env_list)
{
	char	*var;
	int		exit_code;

	exit_code = 0;
	(void)env_list;
	if (cmd_vector[1] != NULL)
		exit_code = ft_atoi_long(cmd_vector[1]);
	else
	{
		var = get_variable(env_list, "?");
		exit_code = ft_atoi_long(var);
		free(var);
	}
	exit(exit_code);
}
