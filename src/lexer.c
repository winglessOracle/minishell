/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/22 14:17:50 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


char	*ft_strtok(char *str, char *delim)
{
	static char	*index;
	char		*start;

	if (str != NULL)
		index = str;
	else if (index == NULL)
		return (NULL);
	start = index;
	while (*index)
	{
		if (ft_strchr(*index, delim))
		{
			*index = '\0';
			index++;
			if (start != index - 1)
				return (start);
			else
			{
				start = index;
				break ;
			}
		}
		index++;		
	}	
}

void	ft_lexer(t_node **list, char *str)
{
//	enum	e_lextype;
	char	*tok;

	//mmm = strdup(line); //do we need to maintain original str?
	tok = ft_strtok(str, ' ');
	while (tok != NULL) 	// convert to lower case?
	{
		//if (strcmp(token, ))
		lstadd_back(list, new_node(99, tok));
		tok = ft_strtok(NULL, ' ');
	}
}


	
	//  switch(getlexerenum(word)) {
			// case WORD1;
				//addnodetolist
				// break;
			//default:
				///donothing
				// break;
		// }
		
// int	getlexerenum(char *token)
// {
// 	if (strcmp(token, ">" == 0 ))
//  		return (GREAT);
//  	else if (strcmp(token, "<" == 0 ))
// 		return (LESS);
// 	else if (strcmp(token, ">>" == 0 ))
// 		return (G_GREAT);
// 	else if (strcmp(token, "<<" == 0 ))
// 		return (L_LESS);
// 	else if (strcmp(token, "|" == 0 ))
// 		return (PIPE);
// 	else if (strcmp(token, "$" == 0 ))
// 		return (VAR);
// 	else if (strcmp(token, " " == 0 ))
// 		return (SPACE);
// 	else if (strcmp(token, "\"" == 0 ))
// 		return (D_QUOTE);
// 	else if (strcmp(token, "\'" == 0 ))
// 		return (S_QUOTE);
// 	else if (strcmp(token, "*" == 0 ))
// 		return (WILD_CARD);
// 	else if (strcmp(token, "&&" == 0 ))
// 		return (AND_AND);
// 	else if (strcmp(token, "||" == 0 ))
// 		return (OR_OR);
// 	else if (strcmp(token, " " == 0 ))
// 		return (SPACE);
// 	else
// 		return (WORD);
// }

