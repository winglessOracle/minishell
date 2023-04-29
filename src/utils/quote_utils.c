/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 22:14:52 by cariencaljo   ########   odam.nl         */
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
	char 	*split;
	
	quote = get_quote_char((*tokens)->type);
	content = ft_strdup("");
	if (quote == '\'')
		split = ft_strdup("\' ");
	else
		split = ft_strdup("\" ");
	words = split_to_list((*tokens)->content, split);
	while (words)
	{
		// print_tokens(words, "in split quotes\n");
		quote_open = 0;
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			words->type = check_sub_content(words, quote, quote_open);
			// printf("content: %s, type: %d\n", words->content, words->type);
			if (words->type)
			{
				// printf("content: %s, expand type: %d\n", words->content, words->type);
				// free(words->content);
				// words->content = content;
				// content = ft_strdup("");
				expand_sub(&words, cmd);
			}
			if (!words->content)
			{
				// printf("no content\n");
				words->content = ft_strdup("");
			}
			content = ft_strjoin_free_s1(content, words->content);
			(*tokens)->type = words->type;
			remove_node(&words, cmd);
		}
		if (words && words->content[0] == quote && quote_open)
		{
			remove_node(&words, cmd);
			if (quote == '\'')
				(*tokens)->type = SQUOTE;
			else
				(*tokens)->type = DQUOTE;
		}
		else if (words && quote_open)
			return(syntax_error(tokens, cmd, "unclosed quotes\n", 1));
		// printf("content: %s\n", content);
	}
	free((*tokens)->content);
	(*tokens)->content = content;
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
	while (quotes != -1 && count_quotes((*token)->content, quote) % 2)
		merge_tokens(*token, type);
	if (!*token)
		return(syntax_error(token, cmd, "unclosed quotes\n", 1));
	// printf("2. before split and remove quotes: %s\n", (*token)->content);
	remove_double_quotes(token);
	split_and_remove_quotes(token, cmd);
	// printf("3. after split and remove quotes: %s, token type: %d, type: %d, quotes: %d\n", (*token)->content, (*token)->type, type, quotes);
	if (quotes == -1)
		(*token)->type = WORD;
	(*token)->type = check_token_content(*token, (*token)->type);
	// printf("4. after split and remove quotes: %s, token type: %d, type: %d\n", (*token)->content, (*token)->type, type);
	if ((*token)->type == DQUOTE || (*token)->type == SQUOTE)
		merge_quoted(token, cmd);
	remove_double_quotes(token);
	// printf("4. after split and remove quotes: %s, token type: %d, type: %d\n", (*token)->content, (*token)->type, type);
	(*token)->type = WORD;
	return (0);
}
