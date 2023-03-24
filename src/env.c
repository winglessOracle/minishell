/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/24 10:18:16 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_list(char **envp, t_node **env_list)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		lstadd_back(env_list, new_node(0, envp[i]));
		i++;
	}
}

void	print_env(t_node **env_list)
{
	t_node	*temp;

	temp = *env_list;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}