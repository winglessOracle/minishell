/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/22 14:18:07 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_lextype
{
	WORD = 0,
	GREAT,
	LESS,
	G_GREAT,
	L_LESS,
	PIPE,
	VAR,
	//OPERATOR,
	//ASSIGN,
	D_QUOTE,
	S_QUOTE,
	WILD_CARD,
	AND_AND,
	OR_OR,
	SPACE,
}	t_lextype;

void	ft_lexer(t_node **list, char *str);
char	*ft_strtok(char *str, char *delim);

#endif

/*error handeling:
1.

*/
