/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/27 15:30:07 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_lextype
{
	WORD = 0,
	SPACE,
	GREAT,
	LESS,
	DLESS,
	DGREAT,
	PIPE,
	TAB,
	NEW_LINE,
	SEMI,
	AND,
	BRACE_O,
	BRACE_C,	
}	t_lextype;

typedef enum e_state
{
	COMMENT = 1,
	D_QUOTE,
	S_QUOTE,
}	t_state;

// char	*ft_strtok(char *str, char *delim);
// void	ft_lexer(t_node **list, char *str);

#endif

/*error handeling:
1.

*/
