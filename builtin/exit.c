/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:37:37 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/15 14:40:43 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(char **cmd_vector, t_node *env_list)
{
	int		exit_code;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)env_list;
	exit_code = 0;
	while (cmd_vector[i])
		i++;
	if (i == 1)
		exit(exit_code);
	if ((cmd_vector[1][j] == '-' || cmd_vector[1][j] == '+') \
		&& cmd_vector[1][j + 1])
		j++;
	if (!ft_strcmp(cmd_vector[1], ""))
		exit__error("exit: numeric argument required", 255);
	while (cmd_vector[1][j])
	{
		if (!ft_isdigit(cmd_vector[1][j]))
			exit__error("exit: numeric argument required", 255);
		j++;
	}
	if (i > 2)
		return (return_error("exit: too many arguments", 1, 1));
	if (cmd_vector[1])
		exit_code = ft_atoi_long(cmd_vector[1]);
	else
		exit_code = g_exit_status;
	exit(exit_code);
}
