/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:31:02 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/15 15:58:49 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h" //test

// static char	*cmd_vector[] = {"cd", "../minishell/src"};
	
// int	test_cd(t_smpl_cmd *cmd, t_node *env_list)
// {
// 	char	*buf;
// 	char	**cmd_args;

// 	buf = NULL;
// 	cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
// 	execute_cd(cmd_args, env_list);
// 	printf("\nnew PWD:\t%s\n", get_variable(env_list, "PWD"));
// 	printf("new OLDPWD:\t%s\n", get_variable(env_list, "OLDPWD"));
// 	free(buf);
// 	return (0);
// }
// int	test_echo()
// {
// 	execute_echo(cmd_vector);
// 	return (0);
// }