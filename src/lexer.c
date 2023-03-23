/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/23 13:26:05 by carlo         ########   odam.nl         */
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
			lstadd_back(list, new_node(getlexerenum(d), NULL));
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

void	ft_lexer(t_node **list, char *str)
{
	char	*token;
	char	*input_line;
	char	*deliminators;
	
	deliminators = " ";
	input_line = ft_strdup(str);
	printf("input_line = %s\n", input_line);
	token = ft_strtok(input_line, deliminators, list);
	while (token != NULL) 	// convert to lower case?
	{
		printf("\ttoken= %s\n", token);
	 	lstadd_secondback(list, new_node(0, (char *)token));
	 	token = ft_strtok(NULL, deliminators, list);
	}
	//swap last nodes?
	free (input_line);
}

int	getlexerenum(char *token)
{
	
	if (ft_strcmp(token, " ") == 0 )
		return (SPACE);
	else if (ft_strcmp(token, ">") == 0 )
 		return (GREAT);
 	else if (ft_strcmp(token, "<") == 0 )
		return (LESS);
	// else if (ft_strcmp(token, ">>") == 0 )
	// 	return (G_GREAT);
	// else if (ft_strcmp(token, "<<") == 0 )
	// 	return (L_LESS);
	else if (ft_strcmp(token, "|") == 0 )
		return (PIPE);
	else if (ft_strcmp(token, "$") == 0 )
		return (VAR);
	else if (ft_strcmp(token, " ") == 0 )
		return (SPACE);
	else if (ft_strcmp(token, "\"") == 0 )
		return (D_QUOTE);
	else if (ft_strcmp(token, "\'") == 0 )
		return (S_QUOTE);
	else if (ft_strcmp(token, "*") == 0 )
		return (WILD_CARD);
	// else if (ft_strcmp(token, "&&") == 0 )
	// 	return (AND_AND);
	// else if (ft_strcmp(token, "||") == 0 )
	// 	return (OR_OR);
	else
		return (WORD);
}
