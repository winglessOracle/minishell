/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/30 17:30:36 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_env(void)
{
	t_node	*env_list;
	char	*temp;

	g_exit_status = 0;
	env_list = environ_to_list();
	add_variable(env_list, ft_strdup("PS1=\x1b[0;36m 💯CC\e[?25h_\e\033[0m"), 1);
	add_variable(env_list, ft_strdup("PS2=> "), 1);
	add_variable(env_list, ft_strdup("IFS=' \t\n'"), 1);
	temp = get_variable(env_list, "HOME");
	add_variable(env_list, ft_strjoin("~=", temp), 1);
	free(temp);
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

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		exit_error("init pipeline", errno);
	ft_memset(list, 0, sizeof(t_list));
	return (list);
}

t_node	*environ_to_list(void)
{
	extern char	**environ;
	t_node		*env_list;
	int			i;

	env_list = NULL;
	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		lstadd_back(&env_list, new_node(2, ft_strdup(environ[i])));
		i++;
	}
	return (env_list);
}
