/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 19:37:37 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/30 09:49:56 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(char **cmd_vector, t_node *env_list)
{
	int		exit_code;
	int		i;
	int j	= 0;

	i = 0;
	exit_code = 0;
	while (cmd_vector[i])
		i++;
	if (i == 1)
		exit(exit_code);
	if (cmd_vector[1][j] == '-' || cmd_vector[1][j] == '+')
		j++;
	if (ft_isdigit(cmd_vector[1][j]) == 0)
		exit_error("numeric argument required\n", 2);
	if (i > 2)
		exit_error("ccs: too many arguments\n", 1);
	if (cmd_vector[1])
		exit_code = ft_atoi_long(cmd_vector[1]);
	else
		exit_code = g_exit_status;
	ft_free_array(cmd_vector);
	lstclear(&env_list, delete_content);
	exit(exit_code);
}
