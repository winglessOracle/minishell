/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 14:01:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/13 15:18:25 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

// pwd []
// Print the absolute pathname of the current working directory. 
// mo options are handled or checked
void	execute_pwd(void)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		exit_error("getcwd", 1);
	printf("%s\n", pwd);
	exit (0);
}