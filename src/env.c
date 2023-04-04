/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/04 09:17:27 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*environ_to_list()
{
	extern char **environ;
	t_node	*env_list;
	int		i;
	
	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		lstadd_back(&env_list, new_node(2,ft_strdup(environ[i])));
		i++;
	}
	return (env_list);
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