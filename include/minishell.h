/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/08 14:15:55 by cariencaljo   ########   odam.nl         */
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
	t_node				*env_list; // not cleared in delete content should only be cleared after fork
	t_node				*redirect;
	t_node				*assign;
	int					cmd_argc;
	t_node				*cmd_argv;
	struct s_smpl_cmd	*prev;
	struct s_smpl_cmd	*next;
}	t_smpl_cmd;

typedef struct s_pipe
{
	int				type;
	t_smpl_cmd		*pipe_argv;
	struct s_pipe	*next;
}	t_pipe;

// utils
void		exit_error(int num);
int			syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg, int err);
int			assign(t_node **token, t_smpl_cmd *cmd); // can be moved to executer?

// list_utils
t_node		*lstlast(t_node *lst);
int			lstlen(t_node *lst);
void		lstadd_back(t_node **lst, t_node *new);
void		lstinsert_lst(t_node **at, t_node *lst);
void		lstdelone(t_node *lst, void (*del)(void *));
void		lstclear(t_node **lst, void (*del)(void *));

// node_utils
t_node		*lstpop(t_node **lst);
t_node		*new_node(int type, char *content);
int			remove_node(t_node **token, t_smpl_cmd *cmd);
void		delete_content(void *content);

// pipe_utils
t_smpl_cmd	*lstlast_pipe(t_smpl_cmd *lst);
void		lstadd_back_pipe(t_smpl_cmd **lst, t_smpl_cmd *new);
void		lstdelone_pipe(t_smpl_cmd *lst, void (*del)(void *));
void		lstclear_pipe(t_smpl_cmd **lst, void (*del)(void *));
void		delete_cmd(void *smpl_cmd);

//lexer
t_node		*lexer(char *str, char *delim);
t_node		*split_to_list(char *str, char *delim);
int			getlexerenum(char token);
void		merge_tokens(t_node *token, int type);

// parser
t_node		*init_env(void);
t_smpl_cmd	*init_smpl_cmd(t_node *env_list);
t_pipe		*init_pipeline(void);
t_node		*parse_pipeline(t_node *tokens, t_node *env_list, t_pipe **pipe);
int			check_token_content(t_node *token, int type);

// environment
t_node		*environ_to_list(void);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
int			update_variable(t_node *env_list, char *name, char *cont, int type);
int			check_env_content(char *str);
void		print_env(t_node *env_list, int flag);

//tests
void		leaks(void);
void		print_env(t_node *env_list, int flag);
void		print_tokens(t_node *tokens, char *str);
void		print_cmd(t_smpl_cmd *cmd);
void		print_pipeline(t_pipe *pipe);

#endif