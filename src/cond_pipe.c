/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cond_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 20:56:59 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/25 15:26:32 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	check_execute_pipe(t_list *list)
{
	while (list->list_argv)
	{
		// check if first command is conditional
		if (!list->list_argv->type)
		{
			executor(list->list_argv);
			list->list_argv = list->list_argv->next;
		}
		else if (list->list_argv->type == AND)
		{
			if (g_exit_status == 0)
			{
				executor(list->list_argv);
				list->list_argv = list->list_argv->next;
			}
			else
			{
				// while (list->list_argv && list->list_argv->state != 0)
				list->list_argv = list->list_argv->next;
				while (list->list_argv && list->list_argv->state != 0)
					list->list_argv = list->list_argv->next;
			}
		}
		else if (list->list_argv->type == OR)
		{
			if (g_exit_status != 0)
			{
				executor(list->list_argv);
				list->list_argv = list->list_argv->next;
			}
			else
			{
				list->list_argv = list->list_argv->next;
				while (list->list_argv && list->list_argv->state != 0 && list->list_argv->type)
					list->list_argv = list->list_argv->next;
			}
		}
		else
			list->list_argv = list->list_argv->next;
		// print_pipeline(list->list_argv);
		// list->list_argv = list->list_argv->next;
		// printf("type: %d, state: %d, exit: %d\n", list->list_argv->type, list->list_argv->state, g_exit_status);
	}
}

void	check_pipe_type(t_node **tokens, t_pipe *pipeline)
{
	while (*tokens)
	{
		// print_tokens(*tokens, "in check_list\n");
		if (!ft_strcmp((*tokens)->content, "&&"))
			pipeline->type = AND;
		if (!ft_strcmp((*tokens)->content, "||"))
			pipeline->type = OR;
		if ((*tokens)->type == PIPE_END)
			remove_node(tokens, NULL);
		if (*tokens && (*tokens)->type == BLANK)
			remove_node(tokens, NULL);
		else
			return ;
	}
	return ;
}
