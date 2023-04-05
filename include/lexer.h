/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/05 11:16:10 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_lextype
{
	WORD = 0,
	BLANK,
	REDIRECT,
	PIPE,
	NEW_LINE,
	// COMMENT,
	// DQUOTE,
	// SQUOTE,
	// EXPAND,
	// ASSIGN,
	// NAME,
	// DLESS,
	// DGREAT,
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
