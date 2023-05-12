/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 20:28:26 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/12 12:19:31 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <sys/types.h>
#include <dirent.h>

void	handle_wildcard(int *counters)
{
	counters[2] = counters[0];
	counters[3] = counters[1];
	counters[1]++;
}
// int *counters, 
// [0]: string_indexer
// [1]: pattern_indexer
// [2]: string_last_match
// [3]: pattern_last_wildcard;
int	match(char *str, char *pattern)
{
	int counters[4];

	ft_memset(counters, 0, sizeof(counters));
	counters[3] = -1;
	while (str[counters[0]])
	{
		if (pattern[counters[1]] == 26)
			handle_wildcard(counters);
		else if (pattern[counters[1]] == str[counters[0]])
		{
			counters[1]++;
			counters[0]++;
		}
		else if (counters[3] != -1)
		{
			counters[1] = counters[3] + 1;
			counters[0] = ++counters[2];
		}
		else 
			return (0);
	}
	while (pattern[counters[1]] == 26) 
		counters[1]++;
	return (pattern[counters[1]] == '\0');
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
