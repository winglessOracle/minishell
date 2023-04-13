/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/12 19:40:16 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/13 10:37:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

// Change the current directory to dir. The variable HOME is the default dir. 
// The variable CDPATH defines the search path for the directory containing dir. 
// Alternative directory names in CDPATH are separated by a colon (:). 
// A null directory name in CDPATH is the same as the current directory, i.e., ''.''. 
// If dir begins with a slash (/), then CDPATH is not used. 
// The -P option says to use the physical directory structure instead of following 
// symbolic links (see also the -P option to the set builtin command); the -L option 
// forces symbolic links to be followed. 
// An argument of - is equivalent to $OLDPWD. If a non-empty directory name from CDPATH 
// is used, or if - is the first argument, and the directory change is successful, 
// the absolute pathname of the new working directory is written to the standard output. 
// The return value is true if the directory was successfully changed; false otherwise.

char	*get_newdir(char *cmd_arg, char *pwd)
{
	char	*dir;
	char	*back;
	int		i;
	
	i = ft_strlen(pwd) - 1;
	while(pwd[i] != '/' && i > 0)
		i--;
	back = ft_substr(pwd, 0, (i + 1));
	pwd = ft_strjoin(pwd, "/");
	if (cmd_arg[0] == '/')
		dir = ft_strdup(cmd_arg);
	else if (cmd_arg[0] == '.' && cmd_arg[1] == '.')
		dir = ft_strjoin(back, cmd_arg);
	else if (cmd_arg[0] == '.')
		dir = ft_strjoin(pwd, &cmd_arg[2]);
	else
		dir = ft_strjoin(pwd, cmd_arg);
	free(back);
	return (dir);
}

int	execute_cd(char **cmd_vector, t_node *env_list)
{
	int		i;
	char	*pwd;
	char	*dir;

	i = 0;
	while (cmd_vector[i])
		i++;
	if (i > 2)
		exit_error("CC|$HELL : cd: too many arguments", 1);  // make dynamic string?
	pwd = get_variable(env_list, "PWD");
	dir = get_newdir(cmd_vector[1], pwd);
	if (chdir(dir) == -1)
		exit_error("chdir", 1);
	add_variable(env_list, ft_strjoin("OLDPWD=", pwd), 2); // free whatever is put in add_variable?
	add_variable(env_list, ft_strjoin("PWD=", dir), 2); // free whatever is put in add_variable?
	free(pwd);
	return(0); //change to exit after testing
}

// The getcwd() function copies an absolute pathname of the current working directory to the array 
// pointed to by buf, which is of length size.

// If the length of the absolute pathname of the current working directory, including the terminating null byte, 
// exceeds size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error, 
// and allocate a larger buffer if necessary.

// As an extension to the POSIX.1-2001 standard, Linux (libc4, libc5, glibc) getcwd() allocates the buffer 
// dynamically using malloc(3) if buf is NULL. In this case, the allocated buffer has the length size unless size is zero, 
// when buf is allocated as big as necessary. The caller should free(3) the returned buffer.
