/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/18 22:54:14 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	get_quote_char(int type)
{
	char	quote;

	if (type == DQUOTE)
		quote = '\"';
	else
		quote = '\'';
	return (quote);
}

int	split_quoted_exp(int nr_q, t_node *token, char **content, t_smpl_cmd *cmd)
{
	int		state;
	char	quote;
	t_node	*words;

	// printf("split exp\n");
	quote = get_quote_char(token->type);
	words = split_to_list(token->content, "\'\"");
	while (words)
	{
		state = check_token_content(words, WORD);
		while (state == EXPAND && token->type != HEREDOC)
		{
			expand(&words, cmd);
			if (words->content)
				state = check_token_content(words, WORD);
			else
				state = WORD;
		}
		if (state == DQUOTE && get_quote_char(token->type) == quote)
			nr_q += 1;
		else if (words->content)
			*content = ft_strjoin_free_s1(*content, words->content);
		remove_node(&words, cmd);
	}
	return (nr_q);
}

int	split_quoted(int nr_quotes, t_node *token, char **content, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;
	t_node	*words;

	quote = get_quote_char(token->type);
	words = split_to_list(token->content, "\'\"");
	while (words)
	{
		type = check_token_content(words, token->type);
		if (type != SQUOTE && type != DQUOTE)
			*content = ft_strjoin_free_s1(*content, words->content);
		else if (get_quote_char(token->type) == quote)
			nr_quotes += 1;
		remove_node(&words, cmd);
	}
	return (nr_quotes);
}

int	get_content(t_node **token, t_smpl_cmd *cmd, int type, int state)
{
	int		nr_quotes;
	char	*content;

	nr_quotes = 0;
	content = NULL;
	while (*token)
	{
		(*token)->type = type;
		if (state == HEREDOC || type == SQUOTE)
			nr_quotes = split_quoted(nr_quotes, *token, &content, cmd);
		else
			nr_quotes = split_quoted_exp(nr_quotes, *token, &content, cmd);
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	if (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)))
		return (-1);
	free((*token)->content);
	(*token)->content = content;
	return (0);
}

int	remove_quotes(t_node **token, t_smpl_cmd *cmd)
{
	int					state;
	int					type;

	state = (*token)->type;
	if (!ft_strcmp((*token)->content, "\"\"") || \
					!ft_strcmp((*token)->content, "\'\'"))
	{
		free((*token)->content);
		(*token)->content = ft_strdup("");
		add_word_to_cmd(token, cmd);
		return (0);
	}
	type = check_token_content(*token, state);
	type = get_content(token, cmd, type, state);
	if (type != -1 && (state == INPUT || state == OUTPUT \
				|| state == APPEND || state == HEREDOC))
	{
		if (state == HEREDOC)
			(*token)->type = HEREDOCQ;
		return (type);
	}
	else if (type != -1)
		add_word_to_cmd(token, cmd);
	return (type);
}
