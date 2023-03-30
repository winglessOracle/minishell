/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 01:58:48 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int	todo(t_node **token);  //remove
int	remove_node(t_node **token);
int	set_type_word(t_node **token);
int	set_cmd_end(t_node **token);

typedef int function(t_node **);

// function  *parse[14] = {
// 	NULL, //word
// 	set_type_word, //dquote
// 	set_type_word, //squote
// 	todo, //expand
// 	todo, //assign
// 	todo, //great
// 	todo, //less
// 	todo, //dless
// 	todo, //dgreat
// 	set_cmd_end, //pipe
// 	set_cmd_end, //new_line should this do more?
// 	remove_node, //comment
// 	remove_node, //space
// 	remove_node, //tab
// };

/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

// %token  WORD
// %token  ASSIGNMENT_WORD
// %token  NAME
// %token  NEWLINE

/* The following are the operators mentioned above. */

// %token  DLESS  DGREAT
// /*      '<<'   '>>' */

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