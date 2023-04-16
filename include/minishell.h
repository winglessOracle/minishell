/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/15 21:02:43 by cariencaljo   ########   odam.nl         */
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
# include <errno.h>

typedef struct s_node
{
	int				type;
	char			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_smpl_cmd
{
	t_node				*env_list;
	t_node				*redirect;
	t_node				*assign;
	int					cmd_argc;
	t_node				*cmd_argv;
	struct s_smpl_cmd	*next;
}	t_smpl_cmd;

typedef struct s_pipe
{
	int				type;
	t_smpl_cmd		*pipe_argv;
	struct s_pipe	*next;
}	t_pipe;

// utils
int			return_error(char *str, int err);
void		exit_error(char	*str, int num);
int			get_exit(t_node *env_list);
char		*get_input(t_node *env_list, char *var);
int			syntax_error(t_node **token, t_smpl_cmd *cmd, char *msg, int err);

// node_utils
t_node		*lstpop(t_node **lst);
t_node		*new_node(int type, char *content);
int			remove_node(t_node **token, t_smpl_cmd *cmd);

// delete_utils
void		delete_content(void *content);
void		delete_cmd(void *smpl_cmd);
void		delete_pipe(void *pipe);

// list_utils
t_node		*lstlast(t_node *lst);
void		lstadd_back(t_node **lst, t_node *new);
void		lstinsert_lst(t_node **at, t_node *lst);
void		lstdelone(t_node *lst, void (*del)(void *));
void		lstclear(t_node **lst, void (*del)(void *));

// cmdlist_utils
t_smpl_cmd	*lstlast_cmd(t_smpl_cmd *lst);
void		lstadd_back_cmd(t_smpl_cmd **lst, t_smpl_cmd *new);
void		lstclear_cmdlst(t_smpl_cmd **lst, void (*del)(void *));
void		lstdelone_cmd(t_smpl_cmd *lst, void (*del)(void *));

//lexer
t_node		*lexer(char *str, char *delim);
t_node		*split_to_list(char *str, char *delim);
int			getlexerenum(char token);
void		merge_tokens(t_node *token, int type);

// init
t_node		*init_env(void);
t_smpl_cmd	*init_smpl_cmd(t_node *env_list);
t_pipe		*init_pipeline(void);

// parser
t_pipe		*parse_pipeline(t_node **tokens, t_node *env_list);
int			check_token_content(t_node *token, int type);

// environment
t_node		*environ_to_list(void);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
int			update_variable(t_node *env_list, char *name, char *cont, int type);
int			check_env_content(char *str);
void		print_env(t_node *env_list, int flag);

//executor
void		assignments(t_smpl_cmd *pipe_argv, pid_t pid, t_node *env_list);
int			executor(t_pipe *pipeline);
int			get_exit_st(t_smpl_cmd *smpl_cmd, pid_t pid);
char		**build_cmd_args(t_node *argv, int argc);
int			get_exit_st(t_smpl_cmd *smpl_cmd, pid_t pid);
char		**get_env(t_node *env_list);

//builtins
int	execute_cd(char **cmd_vector, t_node *env_list);

//tests
void		leaks(void);
void		print_env(t_node *env_list, int flag);
void		print_tokens(t_node *tokens, char *str);
void		print_cmd(t_smpl_cmd *cmd);
void		print_pipeline(t_pipe *pipe);

#endif