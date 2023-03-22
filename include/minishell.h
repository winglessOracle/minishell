/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/22 14:18:42 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include <stdio.h>
# include <errno.h>
// # include <stdbool.h>
// # include <limits.h>

typedef struct s_node
{
	int				type;
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
	
}	t_node;

typedef struct s_master
{
	char	*infile;
	char	*outfile;
	char	*errorfile;
	char	**local_vars;
	t_node	**commands;
	
}	t_master;

void	exit_error(int num);
t_node	*new_node(int type, void *content);
t_node	*lstlast(t_node *lst);
void	lstadd_back(t_node **lst, t_node *new);
void	lstdelone(t_node *lst, void (*del)(void *));
void	lstclear(t_node **lst, void (*del)(void *));

#endif

/*error handeling:
1.
20.	malloc error lexer
*/
