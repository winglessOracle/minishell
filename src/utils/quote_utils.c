/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 11:18:31 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	get_quote_char(int type)
{
	char	quote;

	if (type == DQUOTE)
		quote = '\"';
	else
		quote = '\'';
	return (quote);
}

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
