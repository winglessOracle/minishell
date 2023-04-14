/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:29:13 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/13 20:23:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"
#include <limits.h>

int		execute_echo(char **cmd_vector);
int		execute_cd(char **cmd_vector, t_node *env_list);
void	execute_pwd(void);

// tests
int		test_cd(t_node *env_list);
int		test_echo(void);
int		test_pwd(void);

#endif