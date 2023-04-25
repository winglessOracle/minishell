/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 14:01:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/24 19:41:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

// pwd []
// Print the absolute pathname of the current working directory. 
// no options are handled or checked
int	execute_pwd(char **cmd_vector, t_node *env_list)
{
	char	buf[PATH_MAX];
	char	*pwd;

	(void)cmd_vector;
	pwd = get_variable(env_list, "PWD");
	if (!pwd)
	{
		getcwd(buf, PATH_MAX);
		pwd = ft_strdup(buf);
	}
	if (!pwd)
		return (return_perror("getcwd", 1));
	printf("%s\n", pwd);
	free(pwd);
	ft_free_array(cmd_vector);
	return (0);
}
