/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 10:15:38 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/17 12:10:55 by ccaljouw      ########   odam.nl         */
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
t_node *sort_env(t_node *env_list)
{
	t_node	*temp;
	char	*temp_content;
	
	temp = env_list;
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->content, temp->next->content) > 0)
		{
			printf("temp: %s, next: %s\n", temp->content, temp->next->content);
			temp_content = temp->content;
			temp->next->content = temp->content;
			temp->content = temp_content;
			printf("temp: %s, next: %s\n", temp->content, temp->next->content);
		}
		temp = temp->next;
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
		// print_export(env_list);
	}
	else
	{
		while (cmd_vector[i])
		{
			add_variable(env_list, cmd_vector[i], 3);
			i++;
		}
	}
	return (0);
}