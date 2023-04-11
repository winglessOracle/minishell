/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/11 12:58:40 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	expand_var(t_node **token, t_smpl_cmd *cmd)
{
	char	*str;
	
	remove_node(token, cmd);
	str = get_variable(cmd->env_list, (*token)->content);
	if (!str)
		remove_node(token, cmd);
	else
	{
		free((*token)->content);
		(*token)->content = str;
	}
	return (0);
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;
	char	*str;
	
	words = split_to_list((*token)->content, "$");
	remove_node(token, cmd);
	if (words && words->next)
	{
		if (words->content[0] == '$')
			expand_var(&words, cmd);
		else if (words->next->content[0] == '$')
			expand_var(&words->next, cmd);
		if (words && words->next)
			merge_tokens(words, WORD);
	}
	if (words)
	{
		temp = words;
		str = get_variable(cmd->env_list, "IFS");
		words = split_to_list(temp->content, str);
		free(str);
		remove_node(&temp, cmd);
	}
	lstinsert_lst(token, words);
	return (0);
}

int	expander(t_node **token, t_smpl_cmd *cmd)
{
	int					state;
	static t_function	*parse[10];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_quotes;
	parse[DQUOTE] = remove_quotes;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		state = parse[state](token, cmd);
	}
	return (state);
}
