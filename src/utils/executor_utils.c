/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/21 09:30:42 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	here_doc(t_pipe *pipeline, int *keep)
{
	char	*line_read;
	char	*line;
	t_node	*tokens;

	line = NULL;
	close(*keep);
	*keep = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (*keep < 0)
		exit_error("opening TMP_FILE", 1); //.error or return
	while (1)
	{
		line_read = get_input(pipeline->pipe_argv->env_list, "PS2", 0);
		if (!ft_strcmp(line_read, pipeline->pipe_argv->redirect->content))
			break ;
		tokens = lexer(line_read, " \n");
		line = parse_heredoc(tokens, pipeline->pipe_argv);
		ft_putstr_fd(line, *keep);
		free(line);
	}
	close(*keep);
	*keep = open(TMP_FILE, O_RDONLY);
	if (*keep < 0)
		exit_error("opening TMP_FILE", 1); //error of return
	unlink(TMP_FILE);
}

char	**build_cmd_args(t_node *argv, int argc)
{
	char	**cmd_args;
	int		i;

	i = 0;
	if (!argv || !argc)
		return (NULL);
	cmd_args = malloc(sizeof(char *) * (argc + 1));
	while (i < argc)
	{
		cmd_args[i] = ft_strdup(argv->content);
		remove_node(&argv, NULL);
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}


/*
waitpid: wait for the child process with the specified PID to complete.
WIFEXITED macro: check if the child process exited normally
WEXITSTATUS macro: get the exit status of the child process.
*/
void	set_exit_st(int argc, pid_t *pid)
{
	int	waitstatus;
	int	i;

	i = 0;
	while (i < argc)
	{
		waitpid(pid[i], &waitstatus, 0);
		if (WIFEXITED(waitstatus))
			g_exit_status = WEXITSTATUS(waitstatus);
		i++;
	}
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

void	check_built(t_smpl_cmd *cmd)
{
	t_built	*built[7];
	char	**cmd_args;
	char	*builtings[7] =	{"echo", "cd", "pwd", "export", \
										"unset", "exit", "env"};
	int		i;

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
		if (ft_strcmp(cmd->cmd_argv->content, builtings[i]) == 0)
		{
			cmd_args = build_cmd_args(cmd->cmd_argv, cmd->cmd_argc);
			if (!cmd_args)
				exit_error("building commands", 1);
			g_exit_status = (built[i](cmd_args, cmd->env_list));
		}
		i++;
	}
	g_exit_status = 1;
}
