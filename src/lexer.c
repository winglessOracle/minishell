/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/24 09:53:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	getlexerenum(char token)
{
	if (token == ' ' || token == '\t')
		return (BLANK);
	else if (token == '>' || token == '<')
		return (REDIRECT);
	else if (token == '|')
		return (OR);
	else if (token == '\n')
		return (PIPE_END);
	else if (token == '&')
		return (AND);
	else if (token == '(')
		return (BRACE_O);
	else if (token == ')')
		return (BRACE_C);
	else
		return (WORD);
}

// Creates token list by splitting input line on metacharacters.
// metacharacters: |, <, >, ' ', '\t, '\n'.
// ignores  metacharacters: &, ;, (, ) (not part of the project scope)
t_node	*split_to_list(char *str, char *delim)
{
	t_node	*tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tokens = NULL;
	while (str && str[i] != '\0')
	{
		if (ft_strchr(delim, str[i]))
		{
			if (j != i)
				lstadd_back(&tokens, new_node(WORD, ft_substr(str, j, i - j)));
			lstadd_back(&tokens, new_node(getlexerenum(str[i]), \
														ft_substr(str, i, 1)));
			j = i + 1;
		}
		i++;
	}
	if (j != i)
		lstadd_back(&tokens, new_node(WORD, ft_substr(str, j, i - j)));
	return (tokens);
}

// creates tokens for ther parser that have a token content and type
t_node	*lexer(char *input_line, char *delim)
{
	t_node	*tokens;

	tokens = NULL;
	if (!input_line)
		return (NULL);
	tokens = split_to_list(input_line, delim);
	free(input_line);
	return (tokens);
}
