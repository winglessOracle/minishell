/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 09:29:13 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/17 13:23:28 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <limits.h>

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
char	*get_back(char *cmd_arg, char *pwd);
char	**get_path_arr(t_node *env_list, char *pwd);
void	update_env(t_node *env_list, char *cmd_arg);
char	*new_directory(char *cmd_arg, char *cur_dir);
int		check_dash_arg(char *arg, char **var, char **value, t_node *env_list);
int		go_to_var(t_node *env_list, char *arg, char *var);

// env
void	check_env(t_smpl_cmd *cmd);
t_node	*sort_env(t_node *env_list);

// export
int		check_valid_identifier(char *str);

#endif