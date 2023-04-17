/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/17 16:39:29 by ccaljouw      ########   odam.nl         */
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
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] && str[i + 1])
		return (1);
	return (0);
}

t_node	*change_var(t_node *env_list, char *name, int i)
{
	t_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(temp->content, name, i) == 0 \
							&& temp->content[i + 1] == '=')
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	add_variable(t_node *env_list, char *var, int type)
{
	int		i;
	char	*name;
	t_node	*temp;

	i = 0;		
	while (var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		exit_error("add_variable", 1);
	temp = change_var(env_list, name, i);
	if (temp)
	{
		free(temp->content);
		temp->content = var;
		temp->type = type;
	}
	else
		lstadd_back(&env_list, new_node(type, var));
	free(name);
}

char	*get_variable(t_node *env_list, char *name)
{
	char	*value;
	int		len;
	t_node	*temp;

	value = NULL;
	len = ft_strlen(name);
	temp = env_list;
	while (temp && name)
	{
		if (ft_strncmp(temp->content, name, len) == 0 \
							&& temp->content[len] == '=')
		{
			value = ft_substr(temp->content, (len + 1),
					(ft_strlen(temp->content) - len - 1));
			if (!value)
				exit_error("get_variable", 1);
		}
		temp = temp->next;
	}
	return (value);
}

