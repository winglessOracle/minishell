/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 20:28:26 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/08 16:20:32 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <sys/types.h>
#include <dirent.h>

int	match(char *str, char *pattern)
{
	int	s_indx;
	int	p_indx;

	s_indx = 0;
	p_indx = 0;
	while (str[s_indx] && pattern[p_indx])
	{
		while (str[s_indx] && str[s_indx] == pattern[p_indx])
		{
			s_indx++;
			p_indx++;
		}
		if (pattern[p_indx] == '*')
		{
			while (pattern[p_indx] == '*')
				p_indx++;
			while (str[s_indx] && str[s_indx] != pattern[p_indx])
				s_indx++;
		}
		if (str[s_indx] != pattern[p_indx])
			return (0);
	}
	return (1);
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
	char			*pattern;
	t_node			*temp;

	// print_tokens(token, "args in expand wildcard\n");
	if (!getcwd(buf, PATH_MAX))
		return (NULL);
	pattern = token->content;
	temp = NULL;
	curr_dir = opendir(buf);
	if (curr_dir != NULL)
	{
		file = readdir(curr_dir);
		while (file != NULL)
		{
			if (match(file->d_name, pattern) && file->d_name[0] != '.')
				lstadd_back(&temp, new_node(WORD, ft_strdup(file->d_name)));
			file = readdir(curr_dir);
		}
		closedir(curr_dir);
		sort_argv(temp);
	}
	return (temp);
}

int	check_wildcars(t_node **cmd_args)
{
	t_node	*temp;
	t_node	*new_args;
	int		i;

	new_args = NULL;
	while (*cmd_args)
	{
		i = 0;
		temp = expand_wildcard(*cmd_args);
		if (temp && ft_strcmp((*cmd_args)->content, "") && (*cmd_args)->type != SQUOTE && (*cmd_args)->type != DQUOTE)
			lstadd_back(&new_args, temp);
		else
			lstadd_back(&new_args, \
				new_node(WORD, ft_strdup((*cmd_args)->content)));
		remove_node(cmd_args, NULL);
	}
	*cmd_args = new_args;
	while (new_args)
	{
		new_args = new_args->next;
		i++;
	}
	return (i);
}
