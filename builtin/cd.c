/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 19:40:16 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/13 13:53:55 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

// Change the current directory to dir. The variable HOME is the default dir. 
// The variable CDPATH defines the search path for the directory containing dir. 
// Alternative directory names in CDPATH are separated by a colon (:). 
// A null directory name in CDPATH is the same as the current directory, i.e., ''.''. 
// If dir begins with a slash (/), then CDPATH is not used. 
// An argument of - is equivalent to $OLDPWD. If a non-empty directory name from CDPATH
// is used, or if - is the first argument, and the directory change is successful, 
// the absolute pathname of the new working directory is written to the standard output. 
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

char	*get_newdir(char *cmd_arg, t_node *env_list)
{
	char	*dir;
	char	*cd_path;
	char	*back;

	
	cd_path = get_variable(env_list, "CDPATH");
	if (!cd_path || !*cd_path)
		cd_path = get_variable(env_list, "PWD");
	if (cd_path[ft_strlen(cd_path) - 1] != '/')
		cd_path = ft_strjoin_free_s1(cd_path, "/");
	back = get_back(cd_path);
	if (cmd_arg[0] == '/')
		dir = ft_strdup(cmd_arg);
	else if (cmd_arg[0] == '.' && cmd_arg[1] == '.')
		dir = ft_strjoin(back, &cmd_arg[2]);
	else if (cmd_arg[0] == '-' && cmd_arg[1] == '\0')
		dir = get_variable(env_list, "OLDPWD");
	else if (cmd_arg[0] == '.')
		dir = ft_strjoin(cd_path, &cmd_arg[2]);
	else
		dir = ft_strjoin(cd_path, cmd_arg);
	free(back);
	return (dir);
}

int	execute_cd(char **cmd_vector, t_node *env_list)
{
	// take array or cmd list?
	int		i;
	char	buf[PATH_MAX];
	char	*pwd;
	char	*dir;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 2)
		exit_error("CC|$HELL : cd: too many arguments", 1);  // make dynamic string?
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		exit_error("getcwd", 1);
	add_variable(env_list, ft_strjoin("PWD=", pwd), 2); // 1 or 2?
	dir = get_newdir(cmd_vector[1], env_list);
	if (chdir(dir) == -1)
		exit_error("chdir: dir:", 1); //make dynamic
	add_variable(env_list, ft_strjoin("OLDPWD=", pwd), 2);
	add_variable(env_list, ft_strjoin("PWD=", dir), 2);
	free(dir);
	return(0); //change to exit after testing?
}

