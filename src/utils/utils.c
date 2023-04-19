/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/19 20:40:18 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	 return_perror(char *str, int err)
{
	perror(str);
	return (err);
}

int	 return_error(const char *str, int err)
{
	write(2, str, ft_strlen(str));
	return (err);
}

void	exit_error(char	*str, int num)
{
	perror(str);
	exit(num); //change for exit
}

// prints error message and returns -1 if err != 0;
int	syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg, int err)
{
	if (err != 0)
	{
		write(2, msg, ft_strlen(msg));
		while (*token && (*token)->type != NEW_LINE) // add ;
			remove_node(token, cmd);
		lstclear(&cmd->cmd_argv, delete_content);
		cmd->cmd_argc = 0;
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
	if (line_read && history)
		add_history(line_read);
	free(prompt);
	return (line_read);
}
