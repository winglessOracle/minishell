/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:56:59 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/24 14:54:14 by ccaljouw      ########   odam.nl         */
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

int check_list(t_node **tokens, t_list *list)
{
	if (*tokens && (*tokens)->type == PIPE_END)
	{
		remove_node(tokens, NULL);
	}
	if (!list->type)
	{
		// printf("continue \n");
		return (1);
	}
	// if (list->type == AND && list->state == -1)
	// 	printf("only continue if exit status == 1 to see if all arguments in brackets exit with 1 \n");
	// if (list->type == OR  && list->state == -1)
	// 	printf("only continue if exit status == 0 to see if there is an argument in the brackets that exits 1 \n");
	// if (list->type == AND && list->state == 0)
	// 	printf("only continue if exit status == 1 \n");
	// if (list->type == OR && list->state == 0)
	// 	printf("continue\n");	
	return (0);
}
