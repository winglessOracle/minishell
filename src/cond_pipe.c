/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:56:59 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/25 10:51:35 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		set_brace(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	if ((*token)->type == BRACE_O)
	{
		list->state -= 1;
		remove_node(token, cmd);
		return (0);
	}
	if ((*token)->type == BRACE_C)
	{
		if (list->state == 0)
			syntax_error(token, cmd, "set_cond_pipe\n", 1);
		list->state += 1;
		remove_node(token, cmd);
		return (0);
	}
	return (0);
}

int	check_and(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	(void)cmd;
	(void)list;
	if ((*token)->type == AND)
	{
		if ((*token)->next && (*token)->next->type == AND)
		{
			merge_tokens(*token, AND);
			(*token)->type = PIPE_END;
			return (0);
		}
		else
		{
			(*token)->type = WORD;
			return (0);
		}
	}
	return (0);
}

int	check_or(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	(void)cmd;
	(void)list;
	if ((*token)->type == OR)
	{
		if ((*token)->next && (*token)->next->type == OR)
		{
			merge_tokens(*token, OR);
			(*token)->type = PIPE_END;
			return (0);
		}
		else
		{
			(*token)->type = PIPE;
			return (0);
		}
	}
	return (0);
}

int	cleanup_to_next_pipe(t_node **tokens, t_list *list)
{
	while (*tokens)
	{
		if ((*tokens)->type == AND && list->state == 0)
			check_and(tokens, NULL, list);
		if ((*tokens)->type == OR && list->state == 0)
			check_or(tokens, NULL, list);
		if ((*tokens)->type == PIPE_END)
			break;
		if (*tokens && (*tokens)->type == BRACE_O)
			list->state -= 1;
		if (*tokens && (*tokens)->type == BRACE_C)
		{
			if (list->state == 0)
			{
				syntax_error(tokens, NULL, "check list\n", 1);
				return (1);
			}
			list->state += 1;
			list->type = 0;
		}
		remove_node(tokens, NULL);
	}
	return (1);
}

int check_list(t_node **tokens, t_list *list)
{
	while (*tokens)
	{
		if (!ft_strcmp((*tokens)->content, "&&"))
			list->type = AND;
		if (!ft_strcmp((*tokens)->content, "||"))
			list->type = OR;
		if ((*tokens)->type == PIPE_END)
			remove_node(tokens, NULL);
		if (*tokens && (*tokens)->type == BLANK)
			remove_node(tokens, NULL);
		if (!list->type)
			return (1);
		if (list->type == AND)
		{
			// printf("in AND, exit status: %d\n", g_exit_status);
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
			// printf("in OR, exit status: %d\n", g_exit_status);
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
