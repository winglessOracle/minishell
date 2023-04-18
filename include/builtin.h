/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:29:13 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/18 11:20:49 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"
#include <limits.h>

int		execute_echo(char **cmd_vector, t_node *env_list);
int		execute_cd(char **cmd_vector, t_node *env_list);
int		execute_pwd(char **cmd_vector, t_node *env_list);
int		execute_unset(char **cmd_vector, t_node *env_list);
int		execute_export(char **cmd_vector, t_node *env_list);
int		execute_exit(char **cmd_vector, t_node *env_list);

// cd_utils
char	*get_back(char *pwd);
char	*get_arg(char *cmd_arg, t_node *env_list);
char	**get_path_arr(t_node *env_list, char *pwd);

#endif