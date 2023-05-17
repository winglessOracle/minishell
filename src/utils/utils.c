/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/17 18:34:07 by cariencaljo   ########   odam.nl         */
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

void	warning_heredoc_end(int count, char *delim)
{
	ft_fprintf(2, "cc: warning: here-document at line %d ", count); // shoud this be fd 1?
	ft_fprintf(2, "delimited by end-of-file (wanted '%s')\n", delim); // shoud this be fd 1?
}
