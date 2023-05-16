/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 21:43:08 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/16 15:09:32 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo [-n] [arg ...]
// Output the args, separated by spaces, followed by a newline. 
// The return status is always 0. 
// If -n is specified, the trailing newline is suppressed. 
int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] != 'n' && (str[i] != '\0' || i == 1))
			return (0);
	}
	return (i);
}

int	execute_echo(char **cmd_vector, t_node	*env_list)
{
	int	i;
	int	n;

	(void)env_list;
	i = 1;
	n = 0;
	while (cmd_vector[i] && check_newline(cmd_vector[i]))
	{
		n = 1;
		i++;
	}
	while (cmd_vector[i])
	{
		write(0, cmd_vector[i], ft_strlen(cmd_vector[i]));
		if (cmd_vector[i + 1])
			write(0, " ", 1);
		i++;
	}
	if (!n)
		write(0, "\n", 1);
	return (0);
}
