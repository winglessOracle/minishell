/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 13:01:30 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_parsetype
{
	COMMENT = 1,
	SQUOTE,
	DQUOTE,
	EXPAND,
	ASSIGN,
	// SEMI,
	// AND,
	// BRACE_O,
	// BRACE_C,	
}	t_parsetype;

typedef enum e_redirect
{
	INPUT = 0,
	OUTPUT,
	HEREDOC,
	APPEND,
	ERR,
}	t_redirect;

// parser.c
typedef int function(t_node **, t_smpl_cmd *);

// parser_utils
int	set_cmd_end(t_node **token, t_smpl_cmd *cmd);
int remove_node(t_node **token, t_smpl_cmd *cmd);
int	check_token_content(t_node *token, int type);

// content_utils
int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd);
int	remove_comment(t_node **token, t_smpl_cmd *cmd);
int	remove_squotes(t_node **token, t_smpl_cmd *cmd);
int	remove_dquotes(t_node **token, t_smpl_cmd *cmd);

// redirect_utils
int	redirect_input(t_node **token, t_smpl_cmd *cmd);
int	redirect_output(t_node **token, t_smpl_cmd *cmd);
int	set_here_end(t_node **token, t_smpl_cmd *cmd);
int	set_append(t_node **token, t_smpl_cmd *cmd);


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
// cmd_name         : WORD                   /* Apply rule 7a */
//                  ;
// cmd_word         : WORD                   /* Apply rule 7b */
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
// filename         : WORD                      /* Apply rule 2 */
//                  ;
// io_here          : DLESS     here_end
//                  ;
// here_end         : WORD                      /* Apply rule 3 */
//                  ;

#endif