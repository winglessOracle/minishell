/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:29:13 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/23 17:38:20 by cariencaljo   ########   odam.nl         */
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
int		execute_env(char **cmd_vector, t_node	*env_list);

// cd_utils
int		change_dir(char	*str, char *arg);
char	*get_curr_dir(char *cmd_arg, t_node *env_list);
char	*get_back(char *pwd);
char	**get_path_arr(t_node *env_list, char *pwd);
void	update_env(t_node *env_list, char *cmd_arg);

// env
void	check_env(t_smpl_cmd *cmd);
t_node	*sort_env(t_node *env_list);

#endif