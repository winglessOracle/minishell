/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 20:02:30 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 17:39:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

// unset []
// For each name, remove the corresponding variable or function. 
// Each name refers to a shell variable. Each unset variable is removed from 
// the environment passed to subsequent commands. The exit status is true.
// readonly variables are not part of the scope of this project.
char	*get_name(char	*str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

int	check_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1])
		return (return_error("unset: invallid option", 2, 2));
	if (!str || !ft_strcmp(str, "") || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (return_error("not a valid identifier", 1, 2));
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
				return (return_error("not a valid identifier", 1, 2));
			i++;
		}
		if (str[i] == '=')
			return (return_error("not a valid identifier", 1, 2));
	}
	return (0);
}

int	remove_var(t_node *temp, t_node *prev, char *name)
{
	if (ft_isalpha(name[0]) || name[0] == '_')
	{
		prev->next = temp->next;
		remove_node(&temp, NULL);
		free(name);
		return (1);
	}
	return (0);
}

int	check_and_remove(t_node **temp, char *str, t_node **prev)
{
	char	*name;

	name = get_name((*temp)->content);
	if (!ft_strcmp(str, name))
	{
		if (remove_var(*temp, *prev, name))
			return (1);
	}
	else
	{
		*prev = *temp;
		*temp = (*temp)->next;
	}
	free(name);
	return (0);
}

int	execute_unset(char **cmd_vector, t_node *env_list)
{
	int		i;
	int		check;
	t_node	*temp;
	t_node	*prev;

	i = 1;
	while (cmd_vector[i])
	{
		temp = env_list;
		check = check_valid_unset(cmd_vector[i]);
		if (check)
			return (check);
		while (temp && temp->content)
		{
			if (check_and_remove(&temp, cmd_vector[i], &prev))
				break ;
		}
		i++;
	}
	return (0);
}
