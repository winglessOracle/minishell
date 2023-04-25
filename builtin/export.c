/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 10:15:38 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/24 19:41:44 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Export[]
//  The supplied names are marked for automatic export to the environment of 
//  subsequently executed commands. If no names are given a list of all names 
//  that are exported in this shell is printed. 
//  If a variable name is followed by =word, the value of the variable is set 
//  to word. Export returns an exit status of 0 unless an invalid option is 
//  encountered, one of the names is not a valid shell variable name.
int	check_sorted(t_node *env_list)
{
	t_node	*temp;

	temp = env_list;
	while (temp && temp->next)
	{
		if (ft_strcmp_case(temp->content, temp->next->content, toupper) > 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_node	*sort_env(t_node *env_list)
{
	t_node	*temp;
	char	*temp_content;

	temp = env_list;
	while (!check_sorted(temp))
	{
		while (temp && temp->next)
		{
			if (ft_strcmp_case(temp->content, temp->next->content, toupper) > 0)
			{
				temp_content = temp->content;
				temp->content = temp->next->content;
				temp->next->content = temp_content;
			}
			else
				temp = temp->next;
		}
		temp = env_list;
	}
	return (temp);
}

//flags: 1 = local (default) 2 = external 3 = all (prints everything?)
void	print_export(t_node *env_list)
{
	t_node	*temp;

	temp = env_list;
	while (temp)
	{
		printf("declare -x %s\n", temp->content);
		temp = temp->next;
	}
}

int	execute_export(char **cmd_vector, t_node *env_list)
{
	int	i;

	i = 1;
	if (!cmd_vector[i])
	{
		sort_env(env_list);
		print_export(env_list);
	}
	else
	{
		while (cmd_vector[i])
		{
			if (!ft_isalpha(cmd_vector[i][0]) && cmd_vector[i][0] != '_')
				return (return_error("minishell: export: \
											not a valid identifier\n", 1));
			add_variable(env_list, ft_strdup(cmd_vector[i]), 2);
			i++;
		}
	}
	ft_free_array(cmd_vector);
	return (0);
}
