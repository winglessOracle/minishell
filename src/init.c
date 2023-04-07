/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/07 18:02:50 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_env(void)
{
	t_node	*env_list;
	char	*prompt;

	env_list = environ_to_list();
	prompt = "PS1=\x1b[0;36mCC|$HELL \033[0m";
	add_variable(env_list, prompt, 1);
	add_variable(env_list, "PS2=''", 1);
	add_variable(env_list, "?=test", 1);
	add_variable(env_list, "var=s -l", 1);  //test
	// test 
	// print_env(env_list, 3);
	return (env_list);
}

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
