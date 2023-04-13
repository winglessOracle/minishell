/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/12 21:25:03 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*environ_to_list(void)
{
	extern char	**environ;
	t_node		*env_list;
	int			i;

	env_list = NULL;
	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		lstadd_back(&env_list, new_node(2, ft_strdup(environ[i])));
		i++;
	}
	return (env_list);
}

int	check_env_content(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] && str[i + 1])
		return (1);
	return (0);
}

//type default = 1 (local)
void	add_variable(t_node *env_list, char *content, int type)
{
	int		len;
	char	*name;

	if (!type)
		type = 1; //is this okay?
	if (type < 1 || type > 2)
	{
		printf("Invalid type. Use type 1=local type 2=external\n");
		return ;
	}
	len = 0;
	while (content[len] != '=')
		len++;
	name = ft_substr(content, 0, len);
	if (!update_variable(env_list, name, content, type) && env_list && content)
		lstadd_back(&env_list, new_node(type, content));
	free(name);
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
				exit_error("error in get_variable", errno);
		}
		env_list = env_list->next;
	}
	if (ret)
		return (ret);
	return (NULL);
}

int	update_variable(t_node *env_list, char *name, char *content, int type)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->content, name, ft_strlen(name) + 1) == 0)
		{
			env_list->content = content;
			env_list->type = type;
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}
