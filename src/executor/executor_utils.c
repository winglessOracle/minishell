/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 13:22:26 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/17 15:33:46 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
// void	set_exit_st(int argc, pid_t *pid)
// {
// 	int	waitstatus;
// 	int	i;

// 	i = 0;
// 	waitstatus = 0;
// 	while (i < argc && pid[0] != -5)
// 	{
// 		waitpid(pid[i], &waitstatus, 0);
// 		if (WIFEXITED(waitstatus) && pid[i])
// 			g_exit_status = WEXITSTATUS(waitstatus);
// 		i++;
// 	}
// 	free(pid);
// }

void	set_exit_st(int argc, pid_t *pid)
{
	int	waitstatus;
	int	i;

	i = 0;
	waitstatus = 0;
	while (i < argc && pid[0] != -5)
	{
		waitpid(pid[i], &waitstatus, 0);
		if (WIFEXITED(waitstatus) && pid[i])
			g_exit_status = WEXITSTATUS(waitstatus);
		if (WIFSIGNALED(waitstatus) && pid[i])
		{
			if (WTERMSIG(waitstatus) == 2)
				g_exit_status = 130;
			if (WTERMSIG(waitstatus) == 3)
			{
				g_exit_status = 131;
				printf("Quit (core dumped)\n");
			}
		}
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
		if (curr->type == 2 && ft_strcmp(curr->content, ""))
			arr[i] = ft_strdup(curr->content);
		if (curr->type == 2 && ft_strcmp(curr->content, ""))
			i++;
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_node	*sort_argv(t_node *argv)
{
	t_node	*temp;
	char	*temp_content;

	temp = argv;
	while (!check_sorted_argv(temp))
	{
		while (temp && temp->next)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				temp_content = temp->content;
				temp->content = temp->next->content;
				temp->next->content = temp_content;
			}
			else
				temp = temp->next;
		}
		temp = argv;
	}
	return (temp);
}
