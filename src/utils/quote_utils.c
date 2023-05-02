/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/02 08:31:23 by cariencaljo   ########   odam.nl         */
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
		// print_tokens(words, "in split quoted\n");
		if (words->content[0] == quote)
		{
			// printf("quote: %c\n", quote);
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			// printf("1. str content: %s, quote open: %d\n", content, quote_open);
			if (!quote_open)
				words->type = WORD;
			else
				words->type = (*tokens)->type;
			// printf("1. proces quoted parts. content: %s, type: %d, quote open: %d\n", words->content, words->type, quote_open);
			words->type = check_token_content(words, words->type);
			// printf("2. proces quoted parts. content: %s, type: %d, quote open: %d\n", words->content, words->type, quote_open);
			// printf("2. str content: %s, type: %d\n", content, words->type);
			if (!ft_strcmp(words->content, "$") && words->next && !quote_open)
				expand_var(&words, cmd);
			if (words->type && words->type < 13)
			{
				// printf("expand sub: %d\n", words->type);
				words->type = expand_sub(&words, cmd);
				// print_tokens(words, "after expander in split quotes\n");
			}
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

int	count_quotes(char *str, char quote1)
{
	int		i;
	int		nr_1;
	int		nr_2;
	int		quotes;
	char	quote2;
	
	nr_1 = 0;
	nr_2 = 0;
	// printf("quote 1 is: %c\n", quote1);
	// printf("str in count quotes: %s\n", str);
	if (quote1 == '\'')
		quote2 = '\"';
	else
		quote2 = '\'';
	i = 0;
	while (str[i])
	{
		// printf("str[i]: %c\n", str[i]);
		if (str[i] == quote1 && !((nr_2 % 2)))
		{
			// printf("quote 1\n");
			nr_1++;
		}
		if (str[i] == quote2 && !(nr_1 % 2))
		{
			// printf("quote 2\n");
			nr_2++;
		}
		i++;
	}
	quotes = (nr_1 + nr_2) % 2;
	// printf ("nr_quotes returned: %d\n", quotes);
	return (quotes);
}

void	remove_double_quotes(t_node  **token, char quote)
{
	int	i;
	char *str;
	char *temp;

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
	// int		quotes;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	// printf("1. before split and remove quotes: %s\n", (*token)->content);
	// print_tokens(*token, "before merge quotes\n");
	while (*token && (*token)->next)
	{
		// remove_double_quotes(token, quote);
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
		// printf("token content in merge tokens: %s\n", (*token)->content);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return(syntax_error(token, cmd, "unclosed quotes\n", 1));
	// type = check_token_content(*token, WORD);
	// if (type != (*token)->type)
	// 	return (type);
	// print_tokens(*token, "after merge quotes\n");
	// printf("merge quotes: before split and remove quotes: %s\n", (*token)->content);
	split_and_remove_quotes(token, cmd);
	(*token)->type = type;
	// printf("merge quotes: after split and remove quotes: %s, token type: %d, type: %d, quotes: %d\n", (*token)->content, (*token)->type, type, quotes);
	return (0);
}
