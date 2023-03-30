/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/28 19:08:18 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*env_to_list(char **envp)
{
	t_node	*env_list;
	int		i;
	
	i = 0;
	while (envp[i])
	{
		lstadd_back(&env_list, new_node(2,ft_strdup(envp[i])));
		i++;
	}
	return (env_list);
}

//flags: 1 = local (default) 2 = external 3 = all
void	print_env(t_node *env_list, int flag)
{
	while (env_list)
	{
		if (flag == 1)
		{
			if (env_list->type == 1)
				printf("%s\n", env_list->content);
		}
		if (flag == 2)
		{
			if (env_list->type == 2)  // also prevent printing when var=NULL
				printf("%s\n", env_list->content);
		}
		if (flag == 3)
		 	if (env_list->type == 1 || env_list->type == 2)
				printf("%s\n", env_list->content);		
		env_list = env_list->next;
	}
}

//type default = 1 (local)
void	add_variable(t_node *env_list, char *content, int type)
{
	if (!type)
		type = 1;
	if (env_list && content)
		lstadd_back(&env_list, new_node(type, content));
}

char	*get_variable(t_node *env_list, char *name)
{
	char	*ret;
	
	ret = NULL;
	while (env_list && name)
	{
		if (ft_strncmp(env_list->content, name, ft_strlen(name)) == 0)
		{
			ret = ft_substr(env_list->content, ft_strlen(name) + 1, 
			 	ft_strlen(env_list->content) - (ft_strlen(name) + 1));
			if (!ret)
			 	exit_error(errno);
		}
		env_list = env_list->next;
	}
	if (ret)
		return (ret);
	return (NULL);
}