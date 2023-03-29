/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:03:07 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/29 21:24:09 by cariencaljo   ########   odam.nl         */
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

typedef struct s_smpl_cmd
{
	t_node				*env_list;
	char				*infile;
	char				*outfile;
	char				*errfile;
	char				*here_end;
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

// list_utils_pipe
t_smpl_cmd		*lstlast_pipe(t_smpl_cmd *lst);
void		lstadd_back_pipe(t_smpl_cmd **lst, t_smpl_cmd *new);
// void		lstdelone_pipe(t_smpl_cmd *lst, void (*del)(void *));
// void		lstclear_pipe(t_smpl_cmd **lst, void (*del)(void *));
// void		delete_pipe(void *smpl_cmd);

//lexer
t_node		*lexer(char *str, char *delim);
int			getlexerenum(char token);
int			get_state(char *str);
void		merge_tokens(t_node **token, int type);

// parser
t_smpl_cmd	*init_smpl_cmd(t_node *env_list);
t_pipe		*init_pipeline(void);
t_pipe		*parse_pipeline(t_node *tokens, t_node *env_list);

// environment
t_node		*env_to_list(char **envp);
void		add_variable(t_node *env_list, char *content, int type);
char		*get_variable(t_node *env_list, char *name);
// void		print_env(t_node *env_list, int flag);

//tests
void		leaks(void);
void		print_cmd(t_smpl_cmd *cmd);
void		test_lexer(char *str, t_node *tokens);
void		print_env(t_node *env_list, int flag);

#endif