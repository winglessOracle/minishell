/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/28 19:29:32 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	merge_tokens(t_node *token, int type)
{
	char	*content;

	if (token->next)
	{
		content = ft_strjoin(token->content, token->next->content);
		free(token->content);
		token->content = content;
		token->type = type;
		lstdelone(lst_pop(&token->next), delete_content);
	}
}

int	check_split_tokens(t_node *tokens)
{
	t_node	*temp;
	int		state;

	temp = tokens;
	state = 0;
	while (temp)
	{
		if (temp && ((temp->type == NEW_LINE && state == 1) || state > 1))
			state = 0;
		state = get_state(temp->content);
		if (state == EXPAND || state == ASSIGN)
			temp->type = state;
		if (temp->next && state > 0 && state < 4)
			merge_tokens(temp, state);
		else if (temp->next && temp->type == LESS && temp->next->type == LESS)
			merge_tokens(temp, DLESS);
		else if (temp->next && temp->type == GREAT && temp->next->type == GREAT)
			merge_tokens(temp, DGREAT);
		else
			temp = temp->next;
	}
	if (state == S_QUOTE || state == D_QUOTE)
		return (1);
	return (0);
}

int	getlexerenum(char token)
{
	if (token == ' ')
		return (SPACE);
	else if (token == '>')
		return (GREAT);
	else if (token == '<')
		return (LESS);
	else if (token == '|')
		return (PIPE);
	else if (token == '\t')
		return (TAB);
	else if (token == '\n')
		return (NEW_LINE);
	else if (token == ';')
		return (SEMI);
	else if (token == '&')
		return (AND);
	else if (token == '(')
		return (BRACE_O);
	else if (token == ')')
		return (BRACE_C);
	else
		return (WORD);
}

void	ft_strtok(char *str, char *delim, t_node **tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] != '\0')
	{
		if (ft_strchr(delim, str[i]))
		{
			if (j != i)
				lstadd_back(tokens, new_node(WORD, ft_substr(str, j, i - j)));
			lstadd_back(tokens, new_node(getlexerenum(str[i]), \
														ft_substr(str, i, 1)));
			j = i + 1;
		}
		i++;
	}
	if (j != i)
		lstadd_back(tokens, new_node(WORD, ft_substr(str, j, i - j)));
}

// meta:
// |, <, >, ' ', '\t, '\n'
// ignore  &, ;, (, ) for now
t_node	*lexer(char *input_line, char *delim)
{
	t_node	*tokens;

	tokens = NULL;
	ft_strtok(input_line, delim, &tokens);
	if (check_split_tokens(tokens))
	{
		write(2, "Error, unclosed quotes\n", 23);
		lstclear(&tokens, delete_content);
		return (NULL);
	}
	return (tokens);
}
