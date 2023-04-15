/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 14:01:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/15 16:00:55 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

// pwd []
// Print the absolute pathname of the current working directory. 
// mo options are handled or checked
int	execute_pwd(char **cmd_vector, t_node *env_list)
{
	char	buf[PATH_MAX];
	char	*pwd;

// test remove dir
	(void)cmd_vector;
	(void)env_list;
	pwd = getcwd(buf, PATH_MAX); // test bash with rmdir
	if (!pwd)
		exit_error("getcwd", 1);
	printf("%s\n", pwd);
	return (0);
}