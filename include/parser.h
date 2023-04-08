/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/08 10:33:28 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_parsetype
{
	COMMENT = 5,
	SQUOTE,
	DQUOTE,
	EXPAND,
	ASSIGN,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	// ERR,
	// BRACE_O,
	// BRACE_C,	
}	t_parsetype;

// parser.c
typedef int	t_function(t_node **, t_smpl_cmd *);

// parser_utils
int	check_pipe(t_node *token, t_smpl_cmd *cmd);
int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd);
int	set_cmd_end(t_node **token, t_smpl_cmd *cmd);
int	remove_comment(t_node **token, t_smpl_cmd *cmd);
int	parser_assign(t_node **token, t_smpl_cmd *cmd);

// expand_utils
int	expander(t_node **token, t_smpl_cmd *cmd);
int	expand(t_node **token, t_smpl_cmd *cmd);

// content_utils
int	remove_squotes(t_node **token, t_smpl_cmd *cmd);
int	remove_dquotes(t_node **token, t_smpl_cmd *cmd);
int	remove_dquotes_heredoc(t_node **token, t_smpl_cmd *cmd);

// redirect_utils
int	get_redirect(t_node **tokens, t_smpl_cmd *cmd);

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