/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/24 17:25:24 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strtok(char *str, char *delim, t_node **list)
{
	static char	*last_pos = NULL;
	char		*token_start;
	char		*d;

	if (str != NULL)
		last_pos = str;
	else if (last_pos == NULL)
		return (NULL);
	token_start = last_pos;
	//find start of next token
	while (*last_pos != '\0')
	{
		d = ft_strchr(delim, *last_pos);
		if (d != NULL)
		{
			*last_pos = '\0';
			last_pos++;
			lstadd_back(list, new_node(getlexerenum(*d), NULL));
			if (token_start != last_pos)
				return (token_start);
		}
		last_pos++;
	}
	//no more tokens
	if (token_start == last_pos)
		return (NULL);
	else
		return (token_start);
}

t_node	**lexer(char *str, char *delim)
{
	t_node **tokens;
	char	*token;
	char	*input_line;
	
	tokens = malloc(sizeof(t_node **)); 
	if (!tokens)
		exit_error(21);
	*tokens = NULL;
	input_line = ft_strdup(str);
	token = ft_strtok(input_line, delim, tokens);
	while (token != NULL) 	// convert to lower case?
	{
	 	if (token[0] != '\0' && token)
			lstadd_secondback(tokens, new_node(0, ft_strdup(token)));
		token = ft_strtok(NULL, delim, tokens);
	}
	free (input_line);
	lstswapt_last(tokens);
	return (tokens);
}

int	getlexerenum(char token)
{
	if (token == ' ')
		return (SPACE);
	else if (token == '>')
 		return (GREAT);
 	else if (token == '<')
		return (LESS);
	else if (token == '|')
		return (PIPE);
	else if (token == '\t')
 		return (TAB);
 	else if (token == ';')
		return (SEMI);
	else if (token == '&')
		return (AND);
 	else if (token == '(')
		return (BRACE_O);
	else if (token == ')')
		return (BRACE_C);
	else
		return (WORD);
}
