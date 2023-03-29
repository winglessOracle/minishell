/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 09:45:16 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// if COMMENT || SPACE || TAB -> remove?
// if LESS -> check next and set input 
// if GREAT -> check next and set output TRUNC
// if DLESS -> io_here (set value next node in master_struct?)
// if DGREAT -> check next set output append
// if PIPE -> end simple command
// if NEW_LINE -> end simple command and pipeline
// if EXPAND -> expand to (env)value
	// if $? -> expand to last exit status
// if ASSIGN -> assign variable
