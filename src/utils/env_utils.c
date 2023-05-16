/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/16 20:01:56 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	check_env_content(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (1);
	return (0);
}

t_node	*search_var(t_node *env_list, char *name)
{
	t_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->content, name, ft_strlen(name)) \
			&& (temp->content[ft_strlen(name)] == '=' \
			|| temp->content[ft_strlen(name)] == '\0'))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	replace_var(t_node *temp, char *var, char *name, int type)
{
	free(temp->content);
	temp->content = ft_strdup(var);
	if (temp->content[ft_strlen(name)] == '\0')
		temp->type = 1;
	else
		temp->type = type;
}

void	add_variable(t_node *env_list, char *var, int type)
{
	int		i;
	char	*name;
	char	*content;
	t_node	*temp;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		exit_error("add_variable\n", 1);
	temp = search_var(env_list, name);
	if (temp)
		replace_var(temp, var, name, type);
	else
		lstadd_back(&env_list, new_node(type, ft_strdup(var)));
	if (!ft_strcmp(name, "HOME"))
	{
		content = ft_substr(var, i + 1, ft_strlen(var) - i - 1);
		add_variable(env_list, ft_strjoin("~=", content), 1);
		free(content);
	}
	free(name);
	free(var);
}

char	*get_variable(t_node *env_list, char *name)
{
	char	*value;
	int		len;
	t_node	*temp;

	value = NULL;
	len = 0;
	while (name[len] && name[len] != '=')
		len++;
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
	if (value)
		replace_wildcards(value, '*', 26);
	return (value);
}
