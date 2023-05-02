/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 20:02:30 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/02 15:10:35 by ccaljouw      ########   odam.nl         */
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

void	move_to_next(t_node **temp, t_node **prev)
{
	*prev = *temp;
	*temp = (*temp)->next;
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

int	execute_unset(char **cmd_vector, t_node *env_list)
{
	int		i;
	int		j;
	char	*name;
	t_node	*temp;
	t_node	*prev;

	i = 1;
	j = 0;
	while (cmd_vector[i])
	{
		temp = env_list;
		if (cmd_vector[i][0] == '-' && cmd_vector[i][1])
			return (return_error("minishell: unset: invallid option\n", 2));
		if (check_valid_identifier(cmd_vector[i]))
			return (1);
		while (cmd_vector[i][j])
		{
			if (cmd_vector[i][j] == '=')
				return (return_error("minishell: not a valid identifier\n", 1));
			j++;
		}
		while (temp && temp->content)
		{
			name = get_name(temp->content);
			if (!ft_strcmp(cmd_vector[i], name))
			{
				if (remove_var(temp, prev, name))
					break ;
			}
			else
				move_to_next(&temp, &prev);
			free(name);
		}
		i++;
	}
	return (0);
}
