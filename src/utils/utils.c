/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/11 10:54:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int num)
{
	write(1, "Error\n", 7);
	exit(num);
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

int	get_exit(t_node *env_list)
{
	int		exit_val;
	char	*str;
	
	str = get_variable(env_list, "?");
	exit_val = str[0] - '0';
	free(str);
	return (exit_val);
}

char	*get_input(t_node *env_list, char *var)
{
	char		*prompt;
	char		*line_read;
	
	line_read = NULL;
	prompt = get_variable(env_list, var);
	line_read = readline(prompt);
	if (line_read)
		add_history(line_read);
	free(prompt);
	return (line_read);
}
