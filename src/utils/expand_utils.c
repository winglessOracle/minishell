/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/07 21:53:45 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_words(t_node **words, t_smpl_cmd *cmd, char *content)
{
	char	*temp;

	if ((*words)->content[0] == '$')
	{
		remove_node(words, cmd);
		if (*words && (*words)->content[0] != ' ')
			temp = get_variable(cmd->env_list, (*words)->content);
		else
			temp = ft_strdup((*words)->content);
		remove_node(words, cmd);
		if (temp)
		{
			content = ft_strjoin_free_s1(content, temp);
			free (temp);
		}
	}
	else
	{
		content = ft_strjoin_free_s1(content, ft_strdup((*words)->content));
		remove_node(words, cmd);
	}
	return (content);
}

void	expand_word(t_node **token, t_node *words, t_smpl_cmd *cmd)
{
	t_node	*temp;

	remove_node(&words, cmd);
	free((*token)->content);
	(*token)->content = get_variable(cmd->env_list, words->content);
	(*token)->type = WORD;
	remove_node(&words, cmd);
	words = split_to_list((*token)->content, \
				get_variable(cmd->env_list, "IFS"));
	remove_node(token, cmd);
	if ((*token))
	{
		temp = lstlast(words);
		(*token)->prev = temp;
		temp->next = *token;
	}
	*token = words;
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	char	*content;

	words = split_to_list((*token)->content, "$ ");
	content = NULL;
	if (lstlen(words) > 2)
	{
		while (words)
			content = expand_words(&words, cmd, content);
		if (content)
		{
			free((*token)->content);
			(*token)->content = content;
			(*token)->type = WORD;
		}
	}
	else
		expand_word(token, words, cmd);
	return (0);
}
