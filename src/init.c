/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/14 15:26:28 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_env(void)
{
	t_node	*env_list;

	env_list = environ_to_list();
	add_variable(env_list, "PS1=\x1b[0;36mCC|$HELL \033[0m", 1);
	add_variable(env_list, "PS2=> ", 1);
	add_variable(env_list, "?=0", 1);
	add_variable(env_list, "IFS=' \t\n'", 1);
	// test 
	add_variable (env_list, "VAR=s	-l", 1);  //test
	add_variable (env_list, "2VAR='s -l'", 1);  //test
	// print_env(env_list, 3);
	return (env_list);
}

t_smpl_cmd	*init_smpl_cmd(t_node *env_list)
{
	t_smpl_cmd	*cmd;

	cmd = malloc(sizeof(t_smpl_cmd));
	if (!cmd)
		exit_error("init_smpl_cmd", errno);
	ft_memset(cmd, 0, sizeof(t_smpl_cmd));
	cmd->env_list = env_list;
	return (cmd);
}

t_pipe	*init_pipeline(void)
{
	t_pipe	*pipeline;

	pipeline = malloc(sizeof(t_pipe));
	if (!pipeline)
		exit_error("init pipeline", errno);
	ft_memset(pipeline, 0, sizeof(t_pipe));
	return (pipeline);
}
