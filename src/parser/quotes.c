/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 13:05:03 by cariencaljo   ########   odam.nl         */
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

void	unquoted(t_node **words, t_node **tokens, t_smpl_cmd *cmd, int open)
{
	if (open != -1)
	{
		if (!open)
			(*words)->type = WORD;
		else
			(*words)->type = (*tokens)->type;
		(*words)->type = check_token_content(*words, (*words)->type);
		if (!ft_strcmp((*words)->content, "$") && (*words)->next && !open)
			expand_var(words, cmd);
		if ((*words)->type && (*words)->type < 13)
			(*words)->type = expand_sub(words, cmd);
	}
	if ((*words)->content)
		(*tokens)->content = ft_strjoin_free_s1((*tokens)->content, \
														(*words)->content);
	remove_node(words, cmd);
}

int	split_and_remove_quotes(t_node **tokens, t_smpl_cmd *cmd, int delim)
{
	t_node	*words;
	char	quote;
	char	quote_open;

	quote = get_quote_char((*tokens)->type);
	words = split_to_list((*tokens)->content, "\'\" ");
	free((*tokens)->content);
	(*tokens)->content = ft_strdup("");
	while (words)
	{
		if (words->content[0] == quote)
		{
			if (quote_open)
				quote_open = 0;
			else
				quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote && !delim)
			unquoted(&words, tokens, cmd, quote_open);
		while (words && words->content[0] != quote && delim)
			unquoted(&words, tokens, cmd, -1);
	}
	return (0);
}

int	count_quotes(char *str, char quote1)
{
	int		i;
	int		nr_1;
	int		nr_2;
	int		quotes;
	char	quote2;

	nr_1 = 0;
	nr_2 = 0;
	if (quote1 == '\'')
		quote2 = '\"';
	else
		quote2 = '\'';
	i = 0;
	while (str[i])
	{
		if (str[i] == quote1 && !((nr_2 % 2)))
			nr_1++;
		if (str[i] == quote2 && !(nr_1 % 2))
			nr_2++;
		i++;
	}
	quotes = (nr_1 + nr_2) % 2;
	return (quotes);
}

int	merge_quoted(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (syntax_error(token, cmd, "unclosed quotes\n", 1));
	split_and_remove_quotes(token, cmd, 0);
	(*token)->type = type;
	return (0);
}
