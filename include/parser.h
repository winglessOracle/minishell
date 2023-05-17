/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/05/15 14:41:11 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_parsetype
{
	COMMENT = 9,
	SQUOTE,
	DQUOTE,
	EXPAND,
	ASSIGN,
	ASSIGN_T,
	TILDE,
	INPUT,
	OUTPUT,
	HEREDOC,
	HEREDOCQ,
	APPEND,
}	t_parsetype;

// parser.c
typedef int	t_function(t_node **, t_smpl_cmd *);
typedef int	t_parser(t_node **, t_smpl_cmd *, t_list *);
void		parse_and_execute(t_node *tokens, t_node *env_list);
t_pipe		*parse_pipeline(t_node **tokens, t_node *env_list, t_list *list);
int			check_token_content(t_node *token, int type);

// parser_utils
int			add_word_to_cmd(t_node **token, t_smpl_cmd *cmd);
int			set_cmd_end(t_node **token, t_smpl_cmd *cmd, t_list *list);
int			remove_comment(t_node **token, t_smpl_cmd *cmd);
int			parser_assign(t_node **token, t_smpl_cmd *cmd);
int			expand_tilde(t_node **token, t_smpl_cmd *cmd);

// expand_utils
int			expander(t_node **token, t_smpl_cmd *cmd, t_list *list);
int			expand(t_node **token, t_smpl_cmd *cmd);
int			expand_sub(t_node **token, t_smpl_cmd *cmd);
int			expand_var(t_node **token, t_smpl_cmd *cmd);
int			check_wildcars(t_node **cmd_args);
void		replace_wildcards(char	*str, char replace, char with);

// quotes
char		get_quote_char(int type);
int			count_quotes(char *str, char quote);
int			merge_quoted(t_node **token, t_smpl_cmd *cmd);
int			split_and_remove_quotes(t_node **tokens, \
			t_smpl_cmd *cmd, int delim);
void		unquoted(t_node **words, t_node **tokens, \
			t_smpl_cmd *cmd, int open);

// redirect_utils
int			redirect_tokens(t_node **tokens, t_smpl_cmd *cmd, t_list *list);
int			merge_quoted_heredoc(t_node **token, t_smpl_cmd *cmd, int delim);

// cond_pipe utils
int			set_brace(t_node **token, t_smpl_cmd *cmd, t_list *list);
int			check_and(t_node **token, t_smpl_cmd *cmd, t_list *list);
int			check_or(t_node **token, t_smpl_cmd *cmd, t_list *list);
int			check_braces(t_node **tokens);
int			check_list(t_node **tokens, t_list *list);

#endif