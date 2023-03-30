/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/30 10:53:17 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_lextype
{
	WORD = 0,
	COMMENT,
	D_QUOTE,
	S_QUOTE,
	EXPAND,
	ASSIGN,
	_SPACE,
	GREAT,
	LESS,
	DLESS,
	DGREAT,
	PIPE,
	_TAB,
	NEW_LINE,
	SEMI,
	AND,
	BRACE_O,
	BRACE_C,	
}	t_lextype;


// char	*ft_strtok(char *str, char *delim);
// void	ft_lexer(t_node **list, char *str);

#endif

/*error handeling:
1.

*/
