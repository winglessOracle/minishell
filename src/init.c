/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 20:07:30 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_smpl_cmd	*init_smpl_cmd(t_node *env_list)
{
	t_smpl_cmd	*cmd;

	cmd = malloc(sizeof(t_smpl_cmd));
	if (!cmd)
		exit_error(errno);
	ft_memset(cmd, 0, sizeof(t_smpl_cmd));
	cmd->env_list = env_list;
	return (cmd);
}

t_pipe	*init_pipeline(void)
{
	t_pipe	*pipeline;

	pipeline = malloc(sizeof(t_pipe));
	if (!pipeline)
		exit_error(errno);
	ft_memset(pipeline, 0, sizeof(t_pipe));
	return (pipeline);
}