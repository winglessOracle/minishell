/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/09 20:41:02 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*expand_var(t_node *token, t_smpl_cmd *cmd)
{
	char	*str;
	
	remove_node(&token, cmd);
	str = get_variable(cmd->env_list, (token)->content);
	if (!str)
		remove_node(&token, cmd);
	else
	{
		free((token)->content);
		(token)->content = str;
	}
	return (token);
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;
	
	words = split_to_list((*token)->content, "$");
	remove_node(token, cmd);
	if (words && words->next)
	{
		if (words->content[0] == '$')
			words = expand_var(words, cmd);
		else if (words->next->content[0] == '$')
			words->next = expand_var(words->next, cmd);
			while (words && words->next)
				merge_tokens(words, WORD);
	}
	if (words)
	{
		temp = words;
		words = split_to_list(temp->content, \
				get_variable(cmd->env_list, "IFS"));
		remove_node(&temp, cmd);
		lstinsert_lst(token, words);
	}
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
	// printf("*CHECK CONTENT* %s\n", (*token)->content);
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		state = parse[state](token, cmd);
	}
	return (state);
}
