/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_checks.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/12 11:29:06 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	check_built(t_smpl_cmd *cmd)
{
	int			i;
	t_built		*built[7];
	char		**cmd_args;
	const char	*b[7] = {"echo", "cd", "pwd", "export", "unset", "exit", "env"};

	built[0] = execute_echo;
	built[1] = execute_cd;
	built[2] = execute_pwd;
	built[3] = execute_export;
	built[4] = execute_unset;
	built[5] = execute_exit;
	built[6] = execute_env;
	i = 0;
	while (i < 7 && cmd->cmd_argc > 0)
	{
		if (ft_strcmp(cmd->cmd_argv->content, b[i]) == 0 || \
			ft_strcmp_case(cmd->cmd_argv->content, b[0], ft_tolower) == 0)
		{
			cmd_args = build_cmd_args(&cmd->cmd_argv, cmd->cmd_argc);
			g_exit_status = (built[i](cmd_args, cmd->env_list));
			ft_free_array(cmd_args);
			exit(g_exit_status);
		}
		i++;
	}
}

int	check_builtins_curr_env(t_smpl_cmd *cmd)
{
	t_built		*built[4];
	char		**cmd_args;
	const char	*builtins[4] = {"cd", "exit", "export", "unset"};
	int			i;

	built[0] = execute_cd;
	built[1] = execute_exit;
	built[2] = execute_export;
	built[3] = execute_unset;
	i = 0;
	while (i < 4 && cmd->cmd_argc > 0)
	{
		if (!ft_strcmp(cmd->cmd_argv->content, "export") && cmd->cmd_argc == 1)
			return (0);
		if (ft_strcmp(cmd->cmd_argv->content, builtins[i]) == 0)
		{
			cmd_args = build_cmd_args(&cmd->cmd_argv, cmd->cmd_argc);
			g_exit_status = built[i](cmd_args, cmd->env_list);
			ft_free_array(cmd_args);
			return (1);
		}
		i++;
	}
	return (0);
}

void	check_cmd(char *cmd)
{
	struct stat	file_stat;

	stat(cmd, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
		exit_error("is a directory", 126);
	else if (access(cmd, F_OK) == -1)
		exit_error("command not found", 127);
	else if (access(cmd, X_OK) == -1)
		exit_error("no executable or no permission", 126);
	return ;
}
