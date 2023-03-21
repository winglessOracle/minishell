/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 13:43:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/21 13:44:33 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_commandtype
{
	STD = 0,
	BUILT_IN,
}	t_commandtype;

#endif