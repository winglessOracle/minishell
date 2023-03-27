/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 09:52:22 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/27 18:24:36 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*env_to_list(char **envp)
{
	t_node *env_list;
	int		i;
	
	i = 0;
	env_list = malloc (sizeof(t_node));
	if (!env_list)
		exit_error(errno);
	while (envp[i])
	{
		lstadd_back(&env_list, new_node(2, envp[i]));
		i++;
	}
	return (env_list);
}

//flag defaults to 1 (local)
void	print_env(t_node **env_list, int flag)
{
	t_node	*temp;
	
	temp = *env_list;
	if (!*env_list)
		return ;
	if (!flag)
		flag = 1;
	while (temp)
	{
		if (flag == 1)
		{
			if (temp->type == 1)
				printf("%s\n", (char *)temp->content);
		}
		if (flag == 2)
		{
			if (temp->type == 2)  // also prevent printing when var=NULL
				printf("%s\n", (char *)temp->content);
		}
		if (flag == 3)
		 	if (temp->type == 1 || temp->type == 2)
				printf("%s\n", (char *)temp->content);		
		temp = temp->next;
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

char	*get_var(t_node **env_list, char *name)
{
	t_node	*temp;
	char	*ret;
	
	if (!*env_list || !name) //check with carien
		return NULL;
	temp = *env_list;
	ret = NULL;
	while (temp)
	{
		printf("tet");
		//printf("%s\n", (char *)temp->content);
		// if (ft_strncmp((char *)temp->content, name, ft_strlen(name)) == 0)
		// 	printf("found");
		// 	// ret = ft_substr(temp->content, ft_strlen(name) + 1, 
		// 	// 	ft_strlen(temp->content) - (ft_strlen(name) + 1));
		// 	// if (!ret)
		// 	// 	exit_error(errno);
		// }
		temp = temp->next;
	}
	return (ret);
}
