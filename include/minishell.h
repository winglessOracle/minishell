/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/23 19:14:38 by cariencaljo   ########   odam.nl         */
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

# define TMP_FILE "log/here_doc_tmp"

extern int	g_exit_status;

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
	int					here_doc;
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
int			return_perror(char *str, int err);
int	 		return_error(const char *str, int err);
void		exit_error(char	*str, int num);
char		*get_input(t_node *env_list, char *var, int history);
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
int			remove_cmd_node(t_smpl_cmd **cmds);

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
char		*parse_heredoc(t_node *token, t_node *here_redirect);
int			check_token_content(t_node *token, int type);

// environment
t_node		*environ_to_list(void);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
int			update_variable(t_node *env_list, char *name, char *cont, int type);
int			check_env_content(char *str);
void		print_env(t_node *env_list, int flag);

//executor
void		assignments(t_smpl_cmd *pipe_argv, pid_t pid);
void		executor(t_pipe *pipeline);
char		**build_cmd_args(t_node *argv, int argc);
void		set_exit_st(int argc, pid_t *pid);
char		**get_env(t_node *env_list);
void		check_built(t_smpl_cmd *cmd);
int			check_builtins_curr_env(t_smpl_cmd *cmd);
int			here_doc(t_pipe *pipeline, t_node *here_redirect);

//tests
void		leaks(void);
void		print_env(t_node *env_list, int flag);
void		print_tokens(t_node *tokens, char *str);
void		print_cmd(t_smpl_cmd *cmd);
void		print_pipeline(t_pipe *pipe);

//signals
void		exit_sig(t_node *env_list);

// pattern match
// int			match(char *str, char *pattern);
int			check_wildcars(t_node **cmd_args);

#endif