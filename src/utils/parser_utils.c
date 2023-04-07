/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/07 18:04:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd)
{
	lstadd_back(&cmd->cmd_argv, lstpop(token));
	cmd->cmd_argc++;
	return (0);
}

int	remove_comment(t_node **token, t_smpl_cmd *cmd)
{
	while (*token && (*token)->type != NEW_LINE)
		remove_node(token, cmd);
	return (0);
}

int	parser_assign(t_node **token, t_smpl_cmd *cmd)
{
	if (cmd->cmd_argc != 0)
		return (add_word_to_cmd(token, cmd));
	lstadd_back(&cmd->assign, lstpop(token));
	remove_node(token, cmd);
	return (0);
}

t_node	*expand_word(int var, t_node **words, t_smpl_cmd *cmd)
{
	t_node	*temp;
	
	temp = *words;
	if ((*words)->content[0] == '$')
	{
		remove_node(words, cmd);
		if (*words && (*words)->content[0] != ' ')
			var = 1;
	}
	if (*words)
	{
		if (var == 1)
			(*words)->content = get_variable(cmd->env_list, (*words)->content);
			// if content == ? -> last exit status
	}
	print_tokens(temp);
	return (temp);
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;
	int		var;

	var = 0;
	words = split_to_list((*token)->content, "$ ");
	while (words)
	{
		temp = expand_word(var, &words, cmd);
		if (*token && (*token)->prev)
			(*token)->prev = temp;
		if (*token)
		{
			temp = lstlast(temp);
			temp->next = (*token);
			*token = temp;
		}
		else
			*token = temp;
		var = 0;
	}
	return (0);
}
