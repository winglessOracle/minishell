/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:56:59 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/26 18:15:02 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	cleanup_to_next_pipe(t_node **tokens, t_list *list)
{
	while (*tokens)
	{
		if ((*tokens)->type == AND && list->type == 0)
			check_and(tokens, NULL, list);
		if ((*tokens)->type == OR && list->type == 0)
			check_or(tokens, NULL, list);
		if ((*tokens)->type == PIPE_END)
			break ;
		if (*tokens && (*tokens)->type == BRACE_O)
			list->state -= 1;
		if (*tokens && (*tokens)->type == BRACE_C)
		{
			list->state += 1;
			list->type = 0;
		}
		remove_node(tokens, NULL);
	}
	return (1);
}

int	check_list(t_node **tokens, t_list *list)
{
	while (*tokens)
	{
		if (!ft_strcmp((*tokens)->content, "&&"))
			list->type = AND;
		if (!ft_strcmp((*tokens)->content, "||"))
			list->type = OR;
		if ((*tokens)->type == PIPE_END)
		{
			if (ft_strcmp((*tokens)->content, "&&") \
					&& ft_strcmp((*tokens)->content, "||"))
				list->type = 0;
			remove_node(tokens, NULL);
		}
		if (*tokens && (*tokens)->type == BLANK)
			remove_node(tokens, NULL);
		if (!list->type)
			return (1);
		if (list->type == AND)
		{
			if (g_exit_status == 0)
				return (1);
			if (!*tokens)
			{
				syntax_error(tokens, NULL, "check list\n", 1);
				return (1);
			}
			cleanup_to_next_pipe(tokens, list);
		}
		if (list->type == OR)
		{
			if (g_exit_status != 0)
				return (1);
			if (!*tokens)
			{
				syntax_error(tokens, NULL, "check list\n", 1);
				return (1);
			}
			cleanup_to_next_pipe(tokens, list);
		}
	}
	return (0);
}

int	count_braces(t_node **tokens)
{
	t_node	*temp;
	int		count;

	temp = *tokens;
	count = 0;
	while (*tokens)
	{
		if ((*tokens)->type == BRACE_O)
			count ++;
		if ((*tokens)->type == BRACE_C)
			count --;
		if (count < 0)
			return (1);
		*tokens = (*tokens)->next;
	}
	*tokens = temp;
	return (count);
}
