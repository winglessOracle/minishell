/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 12:30:26 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/20 16:31:37 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env(t_smpl_cmd *cmd)
{
	if (cmd->cmd_argc > 1 && !ft_strcmp(cmd->cmd_argv->content, "env"))
	{
		remove_node(&cmd->cmd_argv, cmd);
		cmd->cmd_argc -= 1;
	}
}

int	execute_env(char **cmd_vector, t_node	*env_list)
{
	int	i;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 1)
		return (return_error("env: has arguments: not handled\n", 1));
	print_env(env_list, 2);
	return (0);
}