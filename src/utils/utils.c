/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:06:30 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/29 09:48:53 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(int type, char *content)
{
	t_node	*new_node;

	if (!content)
		exit_error(errno);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit_error(errno);
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	delete_content(void *content)
{
	char	*temp;

	temp = (char *)content;
	free(temp);
}

void	exit_error(int num)
{
	write(1, "Error\n", 7);
	exit(num);
}
