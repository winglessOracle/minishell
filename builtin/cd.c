/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 19:40:16 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/13 16:30:05 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

// cd []
// Change the current directory to dir. The variable HOME is the default dir. 
// The variable CDPATH defines the search path for the directory containing dir. 
// Alternative directory names in CDPATH are separated by a colon (:). 
// A null directory name in CDPATH is the same as the current directory, i.e., ''.''. 
// An argument of - is equivalent to $OLDPWD. 
// If a non-empty directory name from CDPATH is used, or if - is the first argument, 
// and the directory change is successful, the absolute pathname of the new working 
// directory is written to the standard output. 
// The return value is true if the directory was successfully changed; false otherwise.

char	*get_back(char *cd_path)
{
	int		i;
	char	*back;
	
	i = ft_strlen(cd_path) - 2;
	while(cd_path[i] != '/' && i > 0)
		i--;
	back = ft_substr(cd_path, 0, (i));
	return (back);
}

char	**get_path_arr(char *cmd_arg, char *pwd, t_node *env_list)
{
	char	*dir;
	char	*cd_path;
	char	**path_arr;

	
	cd_path = get_variable(env_list, "CDPATH");
	if (!cd_path)
		cd_path = get_variable(env_list, "PWD");
	path_arr = ft_split(cd_path, ':');
	if (*path_arr)
	{
		if (*path_arr[ft_strlen(*path_arr) - 1] != '/')
			dir = ft_strjoin(*path_arr, "/");
		if (cmd_arg[0] == '/')
			dir = ft_strdup(cmd_arg);
		else if (cmd_arg[0] == '.' && cmd_arg[1] == '.')
			dir = ft_strjoin_free_s1(get_back(pwd), &cmd_arg[2]);
		else if (cmd_arg[0] == '-' && cmd_arg[1] == '\0')
			dir = get_variable(env_list, "OLDPWD");
		else if (cmd_arg[0] == '.')
			dir = ft_strjoin(*path_arr, &cmd_arg[2]);
		else
			dir = ft_strjoin(*path_arr, cmd_arg);
		free(*path_arr);
		*path_arr = dir;
	}
	return (path_arr);
}

int	execute_cd(char **cmd_vector, t_node *env_list)
{
	// take array or cmd list?
	int		i;
	char	buf[PATH_MAX];
	char	*pwd;
	char	**path_arr;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 2)
		exit_error("CC|$HELL : cd: too many arguments", 1);  // make dynamic string?
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		exit_error("getcwd", 1);
	add_variable(env_list, ft_strjoin("PWD=", pwd), 2); // 1 or 2?
	path_arr = get_path_arr(cmd_vector[1], pwd, env_list);
	while (*path_arr)
	{
		i = chdir(*path_arr);
		if ( i == -1)
			path_arr++;
		else
		{
			printf("%s\n", *path_arr);			
			break ;	
		}
	}
	if (i == -1)
		exit_error("chdir: dir", 1); //make dynamic
	add_variable(env_list, ft_strjoin("OLDPWD=", pwd), 2);
	add_variable(env_list, ft_strjoin("PWD=", *path_arr), 2);
	return(0); //change to exit after testing?
}

