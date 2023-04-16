/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 19:40:16 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/16 11:13:21 by cariencaljo   ########   odam.nl         */
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
// The return value is true if the directory was successfully changed; 
// false otherwise.
int	change_dir(char	*str, char *arg, int print)
{
	int	ret;

	if (str[ft_strlen(str) - 1] != '/')
		str = ft_strjoin_free_s1(str, "/");
	str = ft_strjoin_free_s1(str, arg);
	ret = chdir(str);
	if (!ret && print == 1)
		printf("%s\n", str);
	free(str);
	return (ret);
}

int	cd_absolute(char *arg)
{
	if (arg[0] == '/' || arg[0] == '-')
	{
		if (arg[0] == '-' && arg[0] != '\0')
			return_error("minishell: cd: invalid option", 1);
		if (chdir(arg) == -1)
			return_error("minishell: cd", 1);
		else
			return (0);
	}
	return (1);
}

int	cd_relative(t_node *env_list, char *pwd, char *arg, char *buf)
{
	int		i;
	char	**path_arr;
	char	*path;

	i = 0;
	path_arr = get_path_arr(i, env_list, pwd);
	while (path_arr[i])
	{
		if (change_dir(path_arr[i], arg, 1) == -1)
			i++;
		else
			return (0);
	}
	if (!path_arr[i])
	{
		path = getcwd(buf, PATH_MAX);
		if (change_dir(ft_strdup(path), arg, 0) == -1)
			return_error("minishell: cd", 1);
	}
	free(path_arr);
	return (0);
}

int	execute_cd(char **cmd_vector, t_node *env_list)
{
	int		i;
	char	buf[PATH_MAX];
	char	*pwd;
	char	*arg;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 2)
		return_error("minishell: cd: too many arguments", 1);
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		return_error("minishell: cd: getcwd", 1);
	arg = get_arg(cmd_vector[i - 1], pwd, env_list);
	if (!arg)
		return_error("minishell: cd: OLDPWD unset", 1);
	if (cd_absolute(arg))
		if (cd_relative(env_list, pwd, arg, buf))
			return (1);
	free(arg);
	pwd = get_variable(env_list, "PWD");
	add_variable(env_list, ft_strjoin("OLDPWD=", pwd), 2);
	add_variable(env_list, ft_strjoin("PWD=", getcwd(buf, PATH_MAX)), 2);
	free(pwd);
	return (0);
}
