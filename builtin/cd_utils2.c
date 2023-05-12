/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 11:03:39 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 17:37:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dash_arg(char *arg, char **var, char **value, t_node *env_list)
{
	char	*str;

	if (arg[0] == '-' && ft_strcmp(arg, "-"))
	{
		if (!ft_strcmp(arg, "--"))
		{
			*value = get_variable(env_list, "HOME");
			*var = NULL;
			if (*value)
				return (0);
			str = ft_strjoin("HOME", " not set\n");
			ft_putstr_fd(ft_strjoin("cc: cd: ", str), 2);
			free(str);
			return (1);
		}
		else
		{
			ft_putstr_fd("cc: cd: invalid option\n", 2);
			return (1);
		}
	}
	else
		*value = get_variable(env_list, *var);
	return (0);
}

int	go_to_var(t_node *env_list, char *arg, char *var)
{
	char	*value;
	char	*str;

	value = NULL;
	if (check_dash_arg(arg, &var, &value, env_list))
		return (1);
	if (!value)
	{
		str = ft_strjoin(var, " not set\n");
		if (ft_strcmp(var, "OLDPWD"))
			ft_putstr_fd(ft_strjoin("cc: cd: ", str), 2);
		else
			printf("\n");
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
