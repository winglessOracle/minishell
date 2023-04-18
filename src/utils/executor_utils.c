/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/18 09:41:19 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	here_doc(t_pipe *pipeline, int *keep)
{
	char	*line_read;
	//t_node	*tokens;

	close(*keep);
	*keep = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*keep < 0)
		exit_error("opening tmp file", 1);
	while (1)
	{
		line_read = readline("here_doc ");
		if (!ft_strcmp(line_read, pipeline->pipe_argv->redirect->content))
		{
			unlink(TMP_FILE);
			exit(0) ;
		}
		ft_putstr_fd(line_read, *keep);
		free(line_read);
	}
	//	tokens = lexer(line_read, "|<> \t\n");
	//	while (tokens)
	//	{
	//		ft_putstr_fd(tokens->content, *keep);
	//		printf("token=%s\n", tokens->content);
	//		remove_node(&tokens, NULL);
	//	}
}

char	**build_cmd_args(t_node *argv, int argc)
{
	char	**cmd_args;
	int		i;

	i = 0;
	if (!argv || !argc)
		return (NULL);
	cmd_args = malloc(sizeof(char *) * (argc + 1));
	//printf("cmd:%s\n", cmd_args[0]);
	while (i < argc) 
	{
		cmd_args[i] = ft_strdup(argv->content);
		remove_node(&argv, NULL);
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

int	get_exit_st(int argc, pid_t pid)
{
	int	waitstatus;
	int	i;

	i = 0;
	waitstatus = 0;
	while (i < argc)
	{
		waitpid(pid, &waitstatus, 0);
		i++;
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

int	check_built(t_smpl_cmd *cmd)
{
	char	*builtings[6] =	{"echo", "cd", "pwd", "export",	"unset", "env"};
	int		i;
	t_built	*built[6];
	char	**cmd_args;

	built[0] = execute_echo;
	built[1] = execute_cd;
	built[2] = execute_pwd;
	built[3] = execute_export;
	built[4] = execute_unset;
	// built[5] = execute_env;
	i = 0;
	while (i < 6 && cmd->cmd_argc > 0)
	{
		if (ft_strcmp(cmd->cmd_argv->content, "exit") == 0)
		{
			cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
			execute_exit(cmd_args);
		}
		if (ft_strcmp(cmd->cmd_argv->content, builtings[i]) == 0)
		{
			cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
			if (!cmd_args)
				exit_error("building commands", 1);
			return (built[i](cmd_args, cmd->env_list));
		}
		i++;
	}
	return (-1);
}
