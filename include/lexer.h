/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/30 16:15:18 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_lextype
{
	WORD = 0,
	DQUOTE,
	SQUOTE,
	EXPAND,
	ASSIGN,
	GREAT,
	LESS,
	DLESS,
	DGREAT,
	PIPE,
	NEW_LINE,
	COMMENT,
	_SPACE,
	_TAB,
	NAME,
	MAX_TYPE,
	// SEMI,
	// AND,
	// BRACE_O,
	// BRACE_C,	
}	t_lextype;


// char	*ft_strtok(char *str, char *delim);
// void	ft_lexer(t_node **list, char *str);

#endif

/*error handeling:
1.

*/
