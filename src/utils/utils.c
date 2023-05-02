/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/02 13:10:52 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_perror(char *str, int err)
{
	if (err)
		perror(str);
	return (err);
}

int	return_error(const char *str, int err)
{
	write(2, str, ft_strlen(str));
	return (err);
}

void	exit_error(char	*str, int num)
{
	perror(str);
	exit(num);
}

// prints error message and returns -1 if err != 0;
int	syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg, int err)
{
	if (err != 0)
	{
		write(2, msg, ft_strlen(msg));
		while (*token)
			remove_node(token, cmd);
		if (cmd)
		{
			lstclear(&cmd->cmd_argv, delete_content);
			cmd->cmd_argc = 0;
		}
		g_exit_status = 2;
		return (-1);
	}
	else
		return (0);
}

char	*get_input(t_node *env_list, char *var, int history)
{
	char		*prompt;
	char		*line_read;

	line_read = NULL;
	prompt = get_variable(env_list, var);
	line_read = readline(prompt);
	if (line_read && ft_strlen(line_read) > MAX_INPUT_LEN)
	{
		printf("Input exceeds max length of %d characters\n", MAX_INPUT_LEN);
		line_read = NULL;
	}
	if (line_read && history)
		add_history(line_read);
	free(prompt);
	return (line_read);
}
