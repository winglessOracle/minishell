/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 11:03:39 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/19 21:55:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char	*str, char *arg, int print)
{
	int		ret;
	char	buf[PATH_MAX];

	if (print == 1)
		print = ft_strcmp(str, getcwd(buf, PATH_MAX));
	if (str[ft_strlen(str) - 1] != '/')
		str = ft_strjoin_free_s1(str, "/");
	if (arg)
		str = ft_strjoin_free_s1(str, arg);
	ret = chdir(str);
	if (!ret && print)
		printf("%s\n", str);
	free(str);
	return (ret);
}

char	*get_back(char *pwd)
{
	int		i;
	char	*back;

	i = ft_strlen(pwd) - 2;
	while (pwd[i] != '/' && i > 0)
		i--;
	back = ft_substr(pwd, 0, i);
	return (back);
}

char	*get_home(t_node *env_list)
{
	char	*home;
	
	home = get_variable(env_list, "HOME");
	if (!home)
	{
		return_error("minishell: cd: HOME not set\n", 1);
		return(NULL);
	}
	else
		return (home);
}

char	*get_arg(int i, char *cmd_arg, t_node *env_list)
{
	char	*arg;
	char	*pwd;
	char	buf[PATH_MAX];

	if (!cmd_arg)
		return (NULL);
	if (i == 0)
		return(get_home(env_list));
	if (cmd_arg[0] == '/')
		return (ft_strdup(cmd_arg));
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		if (!ft_strcmp(cmd_arg, ".."))
		{
			pwd = get_variable(env_list, "PWD");
			arg = get_back(pwd);
			free(pwd);
		}
		else if (!ft_strcmp(cmd_arg, "."))
		{
			return_error("minishell: cd: error retrieving current directory", 1);
			return (NULL);
		}
		else
		{
			return_error("minishell: cd: no such file of directory\n", 1);
			return (NULL);
		}
	}
	else
		arg = ft_strdup(cmd_arg);
	return (arg);
}

char	**get_path_arr(t_node *env_list, char *pwd)
{
	char	*path;
	char	**path_arr;

	path = get_variable(env_list, "CDPATH");
	if (!path)
		path = ft_strdup(pwd);
	else
	{
		path = ft_strjoin_free_s1(path, ":");
		path = ft_strjoin_free_s1(path, pwd);
	}
	path_arr = ft_split(path, ':');
	free(path);
	return (path_arr);
}
