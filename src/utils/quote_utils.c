/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/01 14:28:40 by ccaljouw      ########   odam.nl         */
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
	
	// printf("in split a nd remove quotes, content: %s, type: %d\n", (*tokens)->content, (*tokens)->type);
	quote = get_quote_char((*tokens)->type);
	// printf("quote now: %c\n", quote);
	content = ft_strdup("");
	words = split_to_list((*tokens)->content, "\'\" ");
	while (words)
	{
		// print_tokens(words, "in split quotes\n");
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			// printf("1. str content: %s\n", content);
			if (!quote_open)
				words->type = WORD;
			else
				words->type = (*tokens)->type;
			words->type = check_token_content(words, (*tokens)->type);
			// printf("proces quoted parts. content: %s, type: %d, quote open: %d\n", words->content, words->type, quote_open);
			// printf("2. str content: %s, type: %d\n", content, words->type);
			if (words->type && words->type < 13 && words->type)
				expand_sub(&words, cmd);
			if (words->content)
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
			// printf("3. str content: %s\n\n", content);
		}
		if (words && words->content[0] == quote && quote_open)
		{
			// printf("remove quote: %c\n", quote);
			quote_open = 0;
			remove_node(&words, cmd);
		}
		// print_tokens(words, "2. in split quotes\n");
		// else if (words && quote_open)
		// 	return(syntax_error(tokens, cmd, "unclosed quotes\n", 1));
		// printf("content: %s\n", content);
	}
	free((*tokens)->content);
	(*tokens)->content = content;
	// printf("end of split quotes, content: %s, type: %d\n", (*tokens)->content, (*tokens)->type);
	// (*tokens)->type = WORD;
	return (0);
}

int	count_quotes(char *str, char quote)
{
	int	i;
	int	nr_quotes;
	// int	nr_double_quotes;

	nr_quotes = 0;
	// nr_double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			if (str[i + 1] == quote)
			{
				// nr_double_quotes++;
				if (nr_quotes == 0)
					return (-1);
				i++;
			}
			else
				nr_quotes++;
		}
		i++;
	}
	// printf ("nr_quotes: %d, nr_double_quotes %d\n", nr_quotes, nr_double_quotes);
	// nr_quotes = (nr_double_quotes * 2) + nr_quotes;
	// printf ("nr_quotes returned: %d\n", nr_quotes);
	return (nr_quotes);
}
void	remove_double_quotes(t_node  **token)
{
	int	i;
	char *str;
	char *temp;

	str = (*token)->content;
	i = ft_strlen(str);
	temp = ft_strdup(str);
	while (1)
	{
		if (str[0] == '\'' && str[1] == '\'')
			temp = ft_substr(str, 2, i - 2);
		else if (str[i - 1] == '\'' && str[i - 2] == '\'')
			temp = ft_substr(str, 0, i - 2);
		else if (str[0] == '\"' && str[1] == '\"')
			temp = ft_substr(str, 2, i - 2);
		else if (str[i - 1] == '\"' && str[i - 2] == '\"')
			temp = ft_substr(str, 0, i - 2);
		else
			break;
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
	int		quotes;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	// printf("1. before split and remove quotes: %s\n", (*token)->content);
	quotes = count_quotes((*token)->content, quote);
	// print_tokens(*token, "before merge quotes\n");
	while (*token && (*token)->next && quotes != -1 && count_quotes((*token)->content, quote) % 2)
		merge_tokens(*token, type);
	// print_tokens(*token, "after merge quotes\n");
	if (!*token || ((count_quotes((*token)->content, quote) % 2) && quotes != -1))
		return(syntax_error(token, cmd, "unclosed quotes\n", 1));
	// remove_double_quotes(token);
	// printf("merge quotes: before split and remove quotes: %s\n", (*token)->content);
	split_and_remove_quotes(token, cmd);
	(*token)->type = type;
	// printf("merge quotes: after split and remove quotes: %s, token type: %d, type: %d, quotes: %d\n", (*token)->content, (*token)->type, type, quotes);
	return (0);
}
