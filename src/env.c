/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/24 14:10:46 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	**env_to_list(char **envp)
{
	t_node **env_list;
	int		i;
	
	i = 0;
	env_list = malloc (sizeof(t_node *));
	if (!env_list)
		exit_error(errno);
	while (envp[i])
	{
		lstadd_back(env_list, new_node(1, envp[i]));
		i++;
	}
	return (env_list);
}

void	print_env(t_node **env_list)
{
	t_node	*temp;

	temp = *env_list;
	while (temp)
	{
		if (temp->type == 1)  // also prevent printing when var=NULL
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}