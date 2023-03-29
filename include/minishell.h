/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/29 10:52:24 by cwesseli      ########   odam.nl         */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// # include <stdbool.h>
// # include <limits.h>

typedef struct s_node
{
	int				type;
	char			*content;
	struct s_node	*prev;
	struct s_node	*next;
	
}	t_node;

typedef struct s_master
{
	char	*infile;
	char	*outfile;
	char	*errfile;
	char	*here_end;
	int		last_exit;  // is dit hier handig?
	t_node	*env_list;
	t_node	*commands;
	
}	t_master;

t_master	*init_master_struct(void);
void		exit_error(int num);
t_node		*new_node(int type, char *content);
t_node		*lstlast(t_node *lst);
void		lstadd_back(t_node **lst, t_node *new);
void		lstadd_front(t_node **lst, t_node *new);
void		lstdelone(t_node *lst, void (*del)(void *));
t_node		*lst_pop(t_node **lst);
void		lstclear(t_node **lst, void (*del)(void *));
void		delete_content(void *content);
void		lstadd_secondback(t_node **lst, t_node *new);
void		lstswapt_last(t_node **lst);

//lexer
// char		*ft_strtok(char *str, char *delim, t_node **list);
t_node		*lexer(char *str, char *delim);

// environment
t_node		*env_to_list(char **envp);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
void		print_env(t_node *env_list, int flag);
int			check_env_content(char *str);

//parser
int			get_state(char *str);

//tests
void		leaks(void);
void		run_tests(char *str, t_node *tokens, t_master *master);
void		test_lexer(char *str, t_node *tokens);

#endif

/*error handeling:
1.
20.	malloc error lexer
*/
