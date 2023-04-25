/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:38:19 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/25 11:38:55 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((*token)->next && (*token)->next->type == AND && BONUS)
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
		if ((*token)->next && (*token)->next->type == OR && BONUS)
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
