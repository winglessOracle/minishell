/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/15 12:15:35 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_perror(char *str, int err)
{
	if (err)
	{
		ft_fprintf(2, "cc: ");
		perror(str);
	}
	return (err);
}

int	return_error(const char *str, int ret, int exit)
{
	ft_fprintf(2, "cc: %s\n", str);
	if (exit)
		g_exit_status = exit;
	return (ret);
}

void	exit_error(char	*str, int num)
{
	ft_fprintf(2, "cc: ");
	perror(str);
	exit(num);
}

void	exit__error(char	*str, int num)
{
	ft_fprintf(2, "cc: %s\n", str);
	exit(num);
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
		line_read = ft_strdup("");
	}
	if (line_read && history)
		add_history(line_read);
	free(prompt);
	return (line_read);
}
