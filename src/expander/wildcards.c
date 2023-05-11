/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 20:28:26 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 15:30:25 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <sys/types.h>
#include <dirent.h>

int	match(char *str, char *pattern)
{
	int s_i;
	int	p_i;
	int s_last_match;
	int p_last_astrix;
	
	s_i = 0;
	p_i = 0;
	s_last_match = 0;
	p_last_astrix = -1;
	while (str[s_i])
	{
		if (pattern[p_i] == 26)
		{
			s_last_match = s_i;
			p_last_astrix = p_i;
			p_i++;
		}
		else if (pattern[p_i] == str[s_i])
		{
			p_i++;
			s_i++;
		}
		else if (p_last_astrix != -1)
		{
			p_i = p_last_astrix + 1;
			s_i = ++s_last_match;
		}
		else return (0);
	}
	while (pattern[p_i] == 26) 
		p_i++;
	return (pattern[p_i] == '\0');
}

int	check_sorted_argv(t_node *argv)
{
	t_node	*temp;

	temp = argv;
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->content, temp->next->content) > 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_node	*sort_argv(t_node *argv)
{
	t_node	*temp;
	char	*temp_content;

	temp = argv;
	while (!check_sorted_argv(temp))
	{
		while (temp && temp->next)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				temp_content = temp->content;
				temp->content = temp->next->content;
				temp->next->content = temp_content;
			}
			else
				temp = temp->next;
		}
		temp = argv;
	}
	return (temp);
}

t_node	*expand_wildcard(t_node *token)
{
	char			buf[PATH_MAX];
	DIR				*curr_dir;
	struct dirent	*file;
	t_node			*temp;

	if (!getcwd(buf, PATH_MAX))
		return (NULL);
	temp = NULL;
	curr_dir = opendir(buf);
	if (curr_dir != NULL)
	{
		file = readdir(curr_dir);
		while (file != NULL)
		{
			if (match(file->d_name, token->content) && (file->d_name[0] != '.' \
				|| token->content[0] == '.') && ft_strcmp(file->d_name, ".") \
				&& ft_strcmp(file->d_name, ".."))
				lstadd_back(&temp, new_node(WORD, ft_strdup(file->d_name)));
			file = readdir(curr_dir);
		}
		closedir(curr_dir);
		sort_argv(temp);
	}
	return (temp);
}

int	check_wildcars(t_node **args)
{
	t_node	*temp;
	t_node	*new_args;
	int		i;

	new_args = NULL;
	while (*args)
	{
		i = 0;
		temp = expand_wildcard(*args);
		if (temp && ft_strcmp((*args)->content, ""))
			lstadd_back(&new_args, temp);
		else
		{
			replace_wildcards((*args)->content, 26, '*');
			lstadd_back(&new_args, new_node(WORD, ft_strdup((*args)->content)));
		}
		remove_node(args, NULL);
	}
	*args = new_args;
	while (new_args)
	{
		new_args = new_args->next;
		i++;
	}
	return (i);
}
