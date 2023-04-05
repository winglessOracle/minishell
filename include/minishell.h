/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/05 12:32:18 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "sigterm.h"
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

typedef struct s_smpl_cmd
{
	t_node				*env_list;
	t_node				*redirect;
	int					cmd_argc;
	t_node				*cmd_argv;
	struct s_smpl_cmd	*next;
}	t_smpl_cmd;

typedef struct s_pipe
{
	int				type;
	int				pipe_argc;
	t_smpl_cmd		*pipe_argv;
	struct s_pipe	*next;
}	t_pipe;

// utils
void		exit_error(int num);

// list_utils
t_node		*lstlast(t_node *lst);
void		lstadd_back(t_node **lst, t_node *new);
void		lstdelone(t_node *lst, void (*del)(void *));
t_node		*lstpop(t_node **lst);
void		lstclear(t_node **lst, void (*del)(void *));

// node_utils
t_node		*new_node(int type, char *content);
void		delete_content(void *content);

// pipe_utils
int			check_pipe(t_node *token, t_smpl_cmd *cmd);
t_smpl_cmd	*lstlast_pipe(t_smpl_cmd *lst);
void		lstadd_back_pipe(t_smpl_cmd **lst, t_smpl_cmd *new);
// void		lstdelone_pipe(t_smpl_cmd *lst, void (*del)(void *));
// void		lstclear_pipe(t_smpl_cmd **lst, void (*del)(void *));
// void		delete_pipe(void *smpl_cmd);

//lexer
t_node		*lexer(char *str, char *delim);
t_node		*split_to_list(char *str, char *delim);
int			getlexerenum(char token);
void		merge_tokens(t_node *token, int type);

// parser
t_node		*init_env(void);
t_smpl_cmd	*init_smpl_cmd(t_node *env_list);
t_pipe		*init_pipeline(void);
t_pipe		*parse_pipeline(t_node *tokens, t_node *env_list);


// environment
t_node		*environ_to_list();
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
int			check_env_content(char *str);
void		print_env(t_node *env_list, int flag);

//parser
int			get_state(char *str);

//tests
void		leaks(void);
void		print_env(t_node *env_list, int flag);
void		print_tokens(t_node *tokens);
void		print_cmd(t_smpl_cmd *cmd);
void		print_pipeline(t_pipe *pipe);

#endif