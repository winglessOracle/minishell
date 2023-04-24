/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:56:59 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/24 16:34:19 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		set_brace(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	if ((*token)->type == BRACE_O)
	{
		// printf("brace open\n");
		if (!list->state)
			list->state = - 1;
		else // moet dit aangepast?
			syntax_error(token, cmd, "set_cond_pipe\n", 1);
		remove_node(token, cmd);
		return (0);
	}
	if ((*token)->type == BRACE_C)
	{
		// printf("brace close\n"); 
		if (list->state != -1)
			syntax_error(token, cmd, "set_cond_pipe\n", 1);
		list->state = 0;
		(*token)->type = PIPE_END;
		return (1);
	}
	return (0);
}

int	check_and(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	(void)cmd;
	if ((*token)->type == AND) // this can create splits that are not supposed to happen. Merge until other spliter, but also back??
	// maybe merge in words when next is not splitter?
	{
		// printf("and\n");
		if ((*token)->next && (*token)->next->type == AND)
		{
			merge_tokens(*token, AND);
			(*token)->type = PIPE_END;
			list->type = AND;
			return (1);
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
	if ((*token)->type == OR)
	{
		// printf("pipe\n");
		if ((*token)->next && (*token)->next->type == OR)
		{
			merge_tokens(*token, OR);
			(*token)->type = PIPE_END;
			list->type = OR;
			return (1);
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
	if ((*tokens)->type == AND)
		check_and(tokens, NULL, list);
	if ((*tokens)->type == OR)
		check_or(tokens, NULL, list);
	while ((*tokens)->type == REDIRECT || (*tokens)->type == WORD || (*tokens)->type == BLANK || (*tokens)->type == PIPE)
		remove_node(tokens, NULL);
	if (*tokens && (*tokens)->type == BRACE_C)
	{
		if (list->state != -1)
		{
			syntax_error(tokens, NULL, "check list\n", 1);
			return (-1);
		}
		list->state = 0;
		remove_node(tokens, NULL);
	}
	// print_tokens(*tokens, "after cleanup\n");
	return (1);
}

int check_list(t_node **tokens, t_list *list)
{
	// printf("exit status: %d\n", g_exit_status);
	if (!*tokens || (*tokens && (*tokens)->type != PIPE_END))
		return (0);
	remove_node(tokens, NULL);
	if (!list->type)
		return (1);
	if (list->type == AND)
	{
	// continue if previous exit satus == 1 else cleanup until next pipe end
		if (g_exit_status == 0)
			return (1);
		if (!*tokens)
			return (0);
		// printf ("AND cleanup\n");
		return (cleanup_to_next_pipe(tokens, list));
	}
	if (list->type == OR)
	{
	// continue if previous exit satus == 0 else cleanup until next pipe end
		if (g_exit_status != 0)
			return (1);
		if (!*tokens)
			return (0);
		// printf ("OR cleanup\n");
		return (cleanup_to_next_pipe(tokens, list));
	}
	return (0);
}
