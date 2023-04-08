/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/08 20:36:20 by cariencaljo   ########   odam.nl         */
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

int	split_quoted(int nr_quotes, t_node *token, char **content, t_smpl_cmd *cmd)
{
	int		type;
	int		state;
	char	quote;
	t_node	*words;
	
	type = (check_token_content(token, token->type));
	quote = get_quote_char(type);
	words = split_to_list(token->content, &quote);
	while (words)
	{
		state = check_token_content(words, WORD);
		while (state == EXPAND && type != SQUOTE)
		{
			expand(&words, cmd);
			state = check_token_content(words, WORD);
		}
		if (state != SQUOTE && state != DQUOTE)
			*content = ft_strjoin_free_s1(*content, words->content);
		else
			nr_quotes += 1;
		remove_node(&words, cmd);
	}
	return (nr_quotes);
}

int	remove_quotes(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	int		state;
	int		type;
	char	*content;

	nr_quotes = 0;
	content = NULL;
	type = check_token_content(*token, (*token)->type);
	while (*token)
	{
		(*token)->type = type;
		nr_quotes = split_quoted(nr_quotes, *token, &content, cmd);
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	if (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)))
		return (-1);
	free((*token)->content);
	(*token)->content = content;
	printf("type: %d\n", type);
	state = add_word_to_cmd(token, cmd);
	return (state);
}

int	remove_quotes_redirect(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	int		state;
	int		type;
	char	*content;

	nr_quotes = 0;
	content = NULL;
	state = (*token)->type;
	if (state == HEREDOC)
		type = SQUOTE;
	else
		type = check_token_content(*token, (*token)->type);
	while (*token)
	{
		(*token)->type = type;
		nr_quotes = split_quoted(nr_quotes, *token, &content, cmd);
		if ((nr_quotes % 2) == 0)
			break ;
		remove_node(token, cmd);
	}
	if (syntax_error(token, cmd, "unclosed quotes\n", (nr_quotes % 2)))
		return (-1);
	remove_node(token, cmd);
	lstadd_back(token, new_node(state, content));
	return (0);
}

int	check_result_remove_quotes_here(t_node **token, char *content)
{
	free((*token)->content);
	(*token)->content = content;
	(*token)->type = check_token_content((*token), DQUOTE);
	return (0);
}

int	remove_quotes_heredoc(t_node **token, t_smpl_cmd *cmd)
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
