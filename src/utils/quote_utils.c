/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/08 10:35:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	remove_squotes(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	char	*content;
	t_node	*words;

	nr_quotes = 0;
	content = NULL;
	while (*token)
	{
		words = split_to_list((*token)->content, "\'");
		while (words)
		{
			if (words->content[0] == '\'')
				nr_quotes += 1;
			else
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	free((*token)->content);
	(*token)->content = content;
	add_word_to_cmd(token, cmd);
	return (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)));
}

int	check_result_remove_quotes(t_node **token, t_smpl_cmd *cmd, char *content)
{
	free((*token)->content);
	(*token)->content = content;
	(*token)->type = check_token_content((*token), DQUOTE);
	if ((*token)->type == EXPAND)
		return (expand(token, cmd));
	else
		return (add_word_to_cmd(token, cmd));
}

int	remove_dquotes(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	char	*content;
	t_node	*words;

	nr_quotes = 0;
	content = NULL;
	while (*token)
	{
		words = split_to_list((*token)->content, "\"");
		while (words)
		{
			if (words->content[0] == '\"')
				nr_quotes += 1;
			else
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	if (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)))
		return (-1);
	return (check_result_remove_quotes(token, cmd, content));
}

int	check_result_remove_quotes_here(t_node **token, char *content)
{
	free((*token)->content);
	(*token)->content = content;
	(*token)->type = check_token_content((*token), DQUOTE);
	return (0);
}

int	remove_dquotes_heredoc(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	char	*content;
	t_node	*words;

	nr_quotes = 0;
	content = NULL;
	// printf("*QUOTES HEREDOC* %s\n", (*token)->content);
	while (*token)
	{
		words = split_to_list((*token)->content, "\"");
		while (words)
		{
			if (words->content[0] == '\"')
				nr_quotes += 1;
			else
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	if (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)))
		return (-1);
	return (check_result_remove_quotes_here(token, content));
}
