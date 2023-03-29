/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/29 15:57:40 by cariencaljo   ########   odam.nl         */
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

// typedef struct s_master
// {
// 	char	*infile;
// 	char	*outfile;
// 	char	*errfile;
// 	char	*here_end;
// 	int		last_exit;  // is dit hier handig?
// 	t_node	*env_list;
// 	t_node	*commands;
	
// }	t_master;

void		exit_error(int num);
t_node		*new_node(int type, char *content);
t_node		*lstlast(t_node *lst);
void		lstadd_back(t_node **lst, t_node *new);
void		lstdelone(t_node *lst, void (*del)(void *));
t_node		*lstpop(t_node **lst);
void		lstclear(t_node **lst, void (*del)(void *));
void		delete_content(void *content);

//lexer
t_node		*lexer(char *str, char *delim);
int			getlexerenum(char token);
int			get_state(char *str);
void		merge_tokens(t_node **token, int type);

// parser
typedef struct s_smpl_cmd
{
	char	*infile;
	char	*outfile;
	char	*errfile;
	char	*here_end;
	t_node	*env_list;
	t_node	*cmd_var;
	
}	t_smpl_cmd;
t_smpl_cmd	*init_smpl_cmd();
t_smpl_cmd	*parse_simple_command(t_node *token, t_smpl_cmd *cmd);

// environment
t_node		*env_to_list(char **envp);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
void		print_env(t_node *env_list, int flag);

//tests
void		leaks(void);
void		run_tests(t_smpl_cmd *cmd, t_node *env_list);
void		test_lexer(char *str, t_node *tokens);

#endif