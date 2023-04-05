/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 16:35:13 by cariencaljo   ########   odam.nl         */
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

int assign(t_node **token, t_smpl_cmd *cmd)
{
	add_variable(cmd->env_list, (*token)->content, 1);
	remove_node(token, cmd);
	return (0);
}

int	expand(t_node **token, t_smpl_cmd *cmd)  //should we handle special characters in a variable?
{
	t_node	*words;
	int		var;
	char	*temp;
	char	*content;

	var = 0;
	words = split_to_list((*token)->content, "$ ");
	content = NULL;
	while (words)
	{
		if (words->content[0] == '$')
		{
			remove_node(&words, cmd);
			if (words && words->content[0] != ' ')
				var = 1;
		}
		if (words && words->content[0] == ' ')
			remove_node(&words, cmd);
		if (words)
		{
			if (var == 1)
				temp = get_variable(cmd->env_list, words->content);
			else
				temp = ft_strdup(words->content);
			remove_node(&words, cmd);
			if (temp)
			{
				content = ft_strjoin_free_s1(content, temp);
				free (temp);
			}
		}
		var = 0;
	}
	if (content)
	{
		free((*token)->content);
		(*token)->content = content;
		(*token)->type = WORD;
	}
	else
		remove_node(token, cmd);
	return (0);
}
