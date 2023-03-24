/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/24 12:11:51 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
// # include <stdbool.h>
// # include <limits.h>

extern char **environ;

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
	t_node	**env_list;
	t_node	**commands;
	
}	t_master;

void	exit_error(int num);
t_node	*new_node(int type, void *content);
t_node	*lstlast(t_node *lst);
void	lstadd_back(t_node **lst, t_node *new);
void	lstdelone(t_node *lst, void (*del)(void *));
void	lstclear(t_node **lst, void (*del)(void *));
void	lstadd_secondback(t_node **lst, t_node *new);
void	lstswapt_last(t_node **lst);

//temp location lexer syuffas in lexer.h they do not recognize t_node
char	*ft_strtok(char *str, char *delim, t_node **list);
void	lexer(t_node **list, char *str, char *delim);
int		getlexerenum(char token);

// environment
void	print_env(t_node **env_list);
void	env_to_list(char **envp, t_node **env_list);

#endif

/*error handeling:
1.
20.	malloc error lexer
*/
