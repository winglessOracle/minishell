/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/09 10:45:35 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	here_doc(t_pipe *pipeline, t_node *here_redirect, t_smpl_cmd *cmd)
{
	int		here_pipe[2];
	char	*line_read;
	char	*line;
	t_node	*tokens;

	line = NULL;
	if (pipe(here_pipe) == -1)
		exit_error("here_pipe fail", errno);
	while (1)
	{
		line_read = get_input(pipeline->pipe_argv->env_list, "PS2", 0);
		if (!ft_strcmp(line_read, here_redirect->content) || line_read == NULL)
			break ;
		tokens = lexer(line_read, " \n");
		line = parse_heredoc(tokens, here_redirect, cmd);
		ft_putstr_fd(line, here_pipe[1]);
		free(line);
	}
	close(here_pipe[1]);
	return (here_pipe[0]);
}

char	**build_cmd_args(t_node **argv, int argc)
{
	t_node	*temp;
	char	**cmd_args;
	int		i;

	i = 0;
	if (!argv || !argc)
		return (NULL);
	if (BONUS)
		argc = check_wildcars(argv);
	temp = *argv;
	cmd_args = malloc(sizeof(char *) * (argc + 1));
	while (i < argc)
	{
		cmd_args[i] = ft_strdup((*argv)->content);
		*argv = (*argv)->next;
		i++;
	}
	cmd_args[i] = NULL;
	*argv = temp;
	return (cmd_args);
}

/*
waitpid: wait for the child process with the specified PID to complete.
WIFEXITED macro: check if the child process exited normally
WEXITSTATUS macro: get the exit status of the child process.
*/
void	set_exit_st(int argc, pid_t *pid, int exit_set)
{
	int	waitstatus;
	int	i;

	i = 0;
	while (i < argc)
	{
		waitpid(pid[i], &waitstatus, 0);
		if (WIFEXITED(waitstatus) && exit_set == 0)
			g_exit_status = WEXITSTATUS(waitstatus);
		i++;
	}
	free(pid);
}

int	get_num_type(t_node *env_list)
{
	t_node	*curr;
	int		i;

	curr = env_list;
	i = 0;
	while (curr)
	{
		if (curr->type == 2)
			i++;
		curr = curr->next;
	}
	return (i);
}

char	**get_env(t_node *env_list)
{
	t_node	*curr;
	char	**arr;
	int		i;

	curr = env_list;
	if (!env_list)
		return (NULL);
	i = get_num_type(env_list);
	arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr = env_list;
	while (curr)
	{
		if (curr->type == 2)
			arr[i] = ft_strdup(curr->content);
		if (curr->type == 2)
			i++;
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}
