/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_n.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:32:12 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 11:13:43 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
int	split_and_remove_quotes(t_node **tokens, t_smpl_cmd *cmd)
{
	t_node	*words;
	char	*content;
	char	quote;
	char	quote_open;
	
	quote = get_quote_char((*tokens)->type);
	content = ft_strdup("");
	words = split_to_list((*tokens)->content, "\'\" ");
	while (words)
	{
		quote_open = 0;
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words->content[0] != quote)
		{
			words->type = check_sub_content(words->content, quote, quote_open);
			if (words->type)
				expand_sub(&words, cmd);
			if (!words->content)
				words->content = ft_strdup("");
			content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if (words->content[0] == quote && quote_open)
			remove_node(&words, cmd);
		else if (quote_open)
			return(syntax_error(tokens, cmd, "unclosed quotes\n", 1));
	}
	free((*tokens)->content);
	(*tokens)->content = content;
	(*tokens)->type = WORD;
	return (0);
}

int	count_quotes(char *str, char quote)
{
	int	i;
	int	nr_quotes;

	nr_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			nr_quotes++;
		i++;
	}
	return (nr_quotes);
}

int	merge_quoted(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (count_quotes((*token)->content, quote) % 2)
		merge_tokens(*token, type);
	if (!*token)
		return(syntax_error(token, cmd, "unclosed quotes\n", 1));
	split_and_remove_quotes(token, cmd);
	(*token)->type = WORD;
	return (0);
}

int	expand_sub(t_node **token, t_smpl_cmd *cmd)
{
	static t_function	*parse[13];

	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	(*token)->type = parse[(*token)->type](token, cmd);
	return ((*token)->type);
}

int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)  //expand word (make separate expander for redirects)
{
	static t_function	*parse[16];
	int					state;

	(void)list;
	state = 0;
	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	parse[TILDE] = expand_tilde;
	while (*token && (*token)->type == WORD && !state)
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		state = parse[(*token)->type](token, cmd);
		if (*token && (*token)->type == WORD)
			add_word_to_cmd(token, cmd);
	}
	return (state);
}
