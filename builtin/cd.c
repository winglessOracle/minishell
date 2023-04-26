/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 19:40:16 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/26 17:55:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <unistd.h>

// cd []
// Change the current directory to dir. The variable HOME is the default dir. 
// The variable CDPATH defines the search path for the directory containing dir
// Alternative directory names in CDPATH are separated by a colon (:). 
// A null directory name in CDPATH is the same as the current directory, 
// i.e., ''.''. 
// If a non-empty directory name from CDPATH is used, or if - is the first 
// argument, and the directory change is successful, the absolute pathname of 
// the new working directory is written to the standard output. 
// An argument of - is equivalent to $OLDPWD.
int	go_to_var(t_node *env_list, char *arg, char *var)
{
	char	*value;
	char	*str;

	if (arg[0] == '-' && ft_strcmp(arg, "-"))
	{
		ft_putstr_fd("minishell: cd: invalid option\n", 2);
		return (1);
	}
	value = get_variable(env_list, var);
	if (!value)
	{
		str = ft_strjoin(var, " not set\n");
		ft_putstr_fd(ft_strjoin("minishell: cd: ", str), 2);
		free(str);
		return (1);
	}
	if (!chdir(value))
	{
		if (!ft_strcmp(var, "OLDPWD"))
			printf("%s\n", value);
		free(value);
		return (0);
	}
	free(value);
	return (1);
}

int	cd_absolute(int i, char *cmd_arg, t_node *env_list)
{
	int	ret;
	
	ret = 2;
	if (!cmd_arg)
		return (0);
	if (i == 1)
		ret = go_to_var(env_list, cmd_arg, "HOME");
	else if (cmd_arg[0] == '-')
		ret = go_to_var(env_list, cmd_arg, "OLDPWD");
	if (cmd_arg[0] == '/')
		ret = chdir(cmd_arg);
	if (ret == -1)
		return(return_perror("minishell: cd", 1));
	return (ret);
}

int	relative_curr_dir(char *cmd_arg, t_node *env_list)
{
	char	*cur_dir;
	char	*new_dir;
	int		ret;

	cur_dir = get_curr_dir(cmd_arg, env_list);
	if (!cur_dir)
		return (1);
	else if (cmd_arg[0] == '.')
	{
		if (cmd_arg[1] == '.')
			new_dir = get_back(cmd_arg, cur_dir);
		else if (ft_strlen(cmd_arg) > 1)
			new_dir = ft_strjoin_free_s1(cur_dir, &cmd_arg[1]);
		else
			new_dir = cur_dir;
	}
	else
	{
		if (cur_dir[ft_strlen(cur_dir) - 1] != '/')
			cur_dir = ft_strjoin_free_s1(cur_dir, "/");
		if (!cur_dir)
			exit_error("cd: strjoin", 1);
		new_dir = ft_strjoin_free_s1(cur_dir, cmd_arg);
		if (!new_dir)
			exit_error("cd: strjoin", 1);
	}
	ret = chdir(new_dir);
	free(new_dir);
	if (ret == -1)
		ret = 1;
	if (!(ret == 1 && cmd_arg[0] != '.'))
		return (return_perror("minishell: cd", ret));
	return (2);
}

int	cd_relative_cdpath(t_node *env_list, char *cmd_arg)
{
	char	**path_arr;
	char	*pwd;
	int		i;

	pwd = get_curr_dir(cmd_arg, env_list);
	if (!pwd)
		return (1);
	path_arr = get_path_arr(env_list, pwd);
	if (!path_arr)
		exit_error("cd", 1);
	i = 0;
	while (path_arr[i])
	{
		if (change_dir(ft_strdup(path_arr[i]), cmd_arg) == -1)
			i++;
		else
		{
			ft_free_array(path_arr);
			free(pwd);
			return (0);
		}
	}
	ft_free_array(path_arr);
	free(pwd);
	return (return_perror("minishell: cd", 1));
}

int	execute_cd(char **cmd_vector, t_node *env_list)
{
	int		i;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 2)
		return (return_error("minishell: cd: too many arguments\n", 1));
	i = cd_absolute(i, cmd_vector[i - 1], env_list);
	if (i == 0)
		update_env(env_list, cmd_vector[i - 1]);
	if (i < 2)
		return (i);
	i = relative_curr_dir(cmd_vector[1], env_list);
	if (i == 0)
		update_env(env_list, cmd_vector[1]);
	if (i < 2)
		return (i);
	i = cd_relative_cdpath(env_list, cmd_vector[1]);
	if (i == 0)
		update_env(env_list, cmd_vector[1]);
	return (i);
}
