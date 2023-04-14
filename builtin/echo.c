/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 21:43:08 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/14 10:37:39 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo [-n] [arg ...]
// Output the args, separated by spaces, followed by a newline. The return status is always 0. 
// If -n is specified, the trailing newline is suppressed. 
int check_newline(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] != 'n' && str[i] != '\0')
			return (0);
	}
	return (i);
}

int	execute_echo(char **cmd_vector)
{
	// take array or cmd list?
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd_vector[i] && check_newline(cmd_vector[i]))
	{
		printf("return newline: %d\n", check_newline(cmd_vector[i]));
		n = 1;
		i++;
	}
	while (cmd_vector[i])
	{
		printf("%s", cmd_vector[i]);
		if (cmd_vector[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	// 
	return(0);
}
