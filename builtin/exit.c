/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:37:37 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/19 09:32:18 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_helper(char **cmd_vector)
{
	int	j;

	j = 0;
	if ((cmd_vector[1][j] == '-' || cmd_vector[1][j] == '+') \
		&& cmd_vector[1][j + 1])
		j++;
	if (!ft_strcmp(cmd_vector[1], ""))
		exit__error("exit: numeric argument required", -1);
	while (cmd_vector[1][j])
	{
		if (!ft_isdigit(cmd_vector[1][j]))
			exit__error("exit: numeric argument required", -1);
		j++;
	}
	if (ft_atoi_long(cmd_vector[1]) > INT_MAX || \
					ft_atoi_long(cmd_vector[1]) < INT_MIN)
		exit__error("exit: numeric argument required", -1);
}

int	execute_exit(char **cmd_vector, t_node *env_list)
{
	long long int		exit_code;
	int					i;

	i = 0;
	(void)env_list;
	if (!cmd_vector)
		exit(g_exit_status);
	exit_code = g_exit_status;
	while (cmd_vector && cmd_vector[i])
		i++;
	if (i == 1)
		exit(exit_code);
	exit_helper(cmd_vector);
	if (i > 2)
		return (return_error("exit: too many arguments", 1, 1));
	if (cmd_vector[1])
	{
		exit_code = ft_atoi_long(cmd_vector[1]);
		if (exit_code > 255)
			exit_code = exit_code % 256;
	}
	exit(exit_code);
}
