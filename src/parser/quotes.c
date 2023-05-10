/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/10 20:12:15 by cariencaljo   ########   odam.nl         */
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

char	get_other_quote(char quote)
{
	char	new_quote;

	if (quote == '\'')
		new_quote = '\"';
	else
		new_quote = '\'';
	return (new_quote);
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
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			if (!quote_open)
				words->type = WORD;
			else
				words->type = (*tokens)->type;
			words->type = check_token_content(words, words->type);
			if (!ft_strcmp(words->content, "$") && words->next && !quote_open)
				expand_var(&words, cmd);
			if (words->type && words->type < 13)
				words->type = expand_sub(&words, cmd);
			if (words->content)
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if (words && words->content[0] == quote && quote_open)
		{
			quote_open = 0;
			remove_node(&words, cmd);
		}
	}
	free((*tokens)->content);
	(*tokens)->content = content;
	return (0);
}

int	count_quotes(char *str, char quote1)
{
	int		i;
	int		nr_1;
	int		nr_2;
	int		quotes;
	char	quote2;

	nr_1 = 0;
	nr_2 = 0;
	if (quote1 == '\'')
		quote2 = '\"';
	else
		quote2 = '\'';
	i = 0;
	while (str[i])
	{
		if (str[i] == quote1 && !((nr_2 % 2)))
			nr_1++;
		if (str[i] == quote2 && !(nr_1 % 2))
			nr_2++;
		i++;
	}
	quotes = (nr_1 + nr_2) % 2;
	return (quotes);
}

void	remove_double_quotes(t_node **token, char quote)
{
	int		i;
	char	*str;
	char	*temp;

	str = (*token)->content;
	i = ft_strlen(str);
	temp = ft_strdup(str);
	while (1)
	{
		if (str[0] == quote && str[1] == quote)
			temp = ft_substr(str, 2, i - 2);
		else if (str[i - 1] == quote && str[i - 2] == quote)
			temp = ft_substr(str, 0, i - 2);
		else
			break ;
		str = temp;
	}
	if (temp)
	{
		free((*token)->content);
		(*token)->content = temp;
	}
}

int	merge_quoted(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (syntax_error(token, cmd, "unclosed quotes\n", 1));
	split_and_remove_quotes(token, cmd);
	(*token)->type = type;
	return (0);
}

int	merge_quoted_heredoc(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (0);
	split_and_remove_quotes(token, cmd);
	return (0);
}

int	split_and_remove_quotes_delim(t_node **tokens, t_smpl_cmd *cmd)
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
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			if (words->content)
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if (words && words->content[0] == quote && quote_open)
		{
			quote_open = 0;
			remove_node(&words, cmd);
		}
	}
	free((*tokens)->content);
	(*tokens)->content = content;
	return (0);
}

int	merge_quoted_heredocdelim(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (0);
	split_and_remove_quotes_delim(token, cmd);
	return (0);
}
