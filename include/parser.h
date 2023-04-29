/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/29 11:18:47 by cariencaljo   ########   odam.nl         */
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

// parser_utils
int		add_word_to_cmd(t_node **token, t_smpl_cmd *cmd);
int		set_cmd_end(t_node **token, t_smpl_cmd *cmd, t_list *list);
int		remove_comment(t_node **token, t_smpl_cmd *cmd);
int		parser_assign(t_node **token, t_smpl_cmd *cmd);
int		expand_tilde(t_node **token, t_smpl_cmd *cmd);

// expand_utils
int		expander(t_node **token, t_smpl_cmd *cmd, t_list *list);
int		expand(t_node **token, t_smpl_cmd *cmd);
int		expand_sub(t_node **token, t_smpl_cmd *cmd);
int		check_sub_content(char *str, char quote, int open);
char	get_quote_char(int type);
int		split_and_remove_quotes(t_node **tokens, t_smpl_cmd *cmd);
int		merge_quoted(t_node **token, t_smpl_cmd *cmd);

// export
int		check_valid_identifier(char *str);

// content_utils
int		remove_quotes(t_node **token, t_smpl_cmd *cmd);

// redirect_utils
int		redirect_tokens(t_node **tokens, t_smpl_cmd *cmd, t_list *list);

// cond_pipe utils
int		set_brace(t_node **token, t_smpl_cmd *cmd, t_list *list);
int		check_and(t_node **token, t_smpl_cmd *cmd, t_list *list);
int		check_or(t_node **token, t_smpl_cmd *cmd, t_list *list);
void	check_pipe_type(t_node **tokens, t_pipe *pipeline);
void	check_execute_pipe(t_pipe *pipe);
int		count_braces(t_node **tokens);
int		check_list(t_node **tokens, t_list *list);

/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

// %token  WORD
// %token  ASSIGNMENT_WORD
// %token  NAME
// %token  NEWLINE
// %token  DLESS  DGREAT

/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */

// start  complete_command

// pipeline         : pipe_sequence
//                  ;
// pipe_sequence    :                   command
//                  | pipe_sequence '|' command
//                  ;
// command          : simple_command
//                  ;
// wordlist         : wordlist WORD
//                  |          WORD
//                  ;
// simple_command   : cmd_prefix cmd_word cmd_suffix
//                  | cmd_prefix cmd_word
//                  | cmd_prefix
//                  | cmd_name cmd_suffix
//                  | cmd_name
//                  ;
// cmd_name         : WORD                   
//* Apply rule 7a */
//                  ;
// cmd_word         : WORD                   
//* Apply rule 7b */
//                  ;
// cmd_prefix       :            io_redirect
//                  | cmd_prefix io_redirect
//                  |            ASSIGNMENT_WORD
//                  | cmd_prefix ASSIGNMENT_WORD
//                  ;
// cmd_suffix       :            io_redirect
//                  | cmd_suffix io_redirect
//                  |            WORD
//                  | cmd_suffix WORD
//                  ;
// redirect_list    :               io_redirect
//                  | redirect_list io_redirect
//                  ;
// io_redirect      :           io_file
//                  |           io_here
//                  ;
// io_file          : '<'       filename
//                  | '>'       filename
//                  | DGREAT    filename
//                  ;
// filename         : WORD                      
//* Apply rule 2 */ -> perform all other rules
//                  ;
// io_here          : DLESS     here_end
//                  ;
// here_end         : WORD                      
//* Apply rule 3 */ -> only perform quote removal
//                  ;

#endif