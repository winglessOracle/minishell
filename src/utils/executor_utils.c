/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/16 20:46:42 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_cmd_args(t_node *argv, int argc)
{
	char	**cmd_args;
	int		i;

	i = 0;
	// if (!argv || !argc)
	// 	return (NULL);
	cmd_args = malloc(sizeof(char *) * (argc + 1));
	while (i < argc)
	{
		if (argv->content)
			cmd_args[i] = ft_strdup(argv->content);
		else
			cmd_args[i] = ft_strdup("");
		remove_node(&argv, NULL);
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

int	get_exit_st(t_smpl_cmd *smpl_cmd, pid_t pid)
{
	int	waitstatus;

	waitstatus = 0;
	while (smpl_cmd)
	{
		waitpid(pid, &waitstatus, 0);
		smpl_cmd = smpl_cmd->next;
	}
	return (WEXITSTATUS(waitstatus));
}

char	**get_env(t_node *env_list)
{
	t_node	*curr;
	char	**str;
	int		i;

	curr = env_list;
	i = 0;
	if (!env_list)
		return (NULL);
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	str = malloc(sizeof(char *) * i);
	i = 0;
	curr = env_list;
	while (curr)
	{
		str[i] = ft_strdup(curr->content);
		curr = curr->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}