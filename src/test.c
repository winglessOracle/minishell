/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:31:02 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/13 10:34:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h" //test

static char	*cmd_vector[] = {"cd", "src"};
	
int	test_cd(t_node *env_list)
{
	char	*buf;

	buf = NULL;
	printf("\ncurrent dir:\t%s\n", getwd(buf));
	printf("current PWD:\t%s\n", get_variable(env_list, "PWD"));
	printf("current OLDPWD:\t%s\n", get_variable(env_list, "OLDPWD"));
	execute_cd(cmd_vector, env_list);
	printf("\nnew dir:\t%s\n", getwd(buf));
	printf("new PWD:\t%s\n", get_variable(env_list, "PWD"));
	printf("new OLDPWD:\t%s\n\n", get_variable(env_list, "OLDPWD"));
	free(buf);
	return (0);
}