/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 11:03:39 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/18 09:48:10 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char	*str, char *arg, int print)
{
	int		ret;
	char	buf[PATH_MAX];

	if (print)
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

char	*get_arg(char *cmd_arg)
{
	char	*arg;
	char	*pwd;
	char	buf[PATH_MAX];

	if (!cmd_arg)
		return (NULL);
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		perror("minishell: cd: getcwd");
		return (NULL);
	}
	if (cmd_arg[0] == '/')
		arg = ft_strdup(cmd_arg);
	else if (cmd_arg[0] == '.' && cmd_arg[1] == '.')
		arg = ft_strjoin_free_s1(get_back(pwd), &cmd_arg[2]);
	else if (cmd_arg[0] == '-' && cmd_arg[1] == '\0')
		arg = ft_strdup("-");
	else if (cmd_arg[0] == '.')
		arg = ft_strdup(&cmd_arg[2]);
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
