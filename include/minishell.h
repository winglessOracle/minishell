/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/21 13:44:39 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
// # include <stdbool.h>
// # include <limits.h>
# include <stdio.h>

typedef struct s_node
{
	int				type;
	char			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef enum e_lextype
{
	WORD = 0,
	GREAT,
	LESS,
	G_GREAT,
	L_LESS,
	PIPE,
	VAR,
	OPERATOR,
	ASSIGN,
	D_QUOTE,
	S_QUOTE,
	WILD_CARD,
	AND_AND,
	OR_OR,
}	t_lextype;

typedef struct s_master
{
	char	*infile;
	char	*outfile;
	char	*errorfile;
	char	**local_vars;
	t_node	**commands;
	
}	t_master;



#endif

/*error handeling:
1.

*/
