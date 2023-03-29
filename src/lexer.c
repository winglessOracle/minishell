/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 16:19:07 by carlo         #+#    #+#                 */
/*   Updated: 2023/03/29 10:09:33 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Checks for states where token should not have been split om metacharacters 
// and merges these nodes back to one token
int	check_split_tokens(t_node *tokens)
{
	t_node	*t;
	int		state;

	t = tokens;
	state = 0;
	while (t)
	{
		if ((t->type == NEW_LINE && state == COMMENT) \
									|| (state == DQUOTE || state == SQUOTE))
			state = 0;
		state = get_state(t->content);
		if (state == EXPAND || state == ASSIGN)
			t->type = state;
		if (t->next && (state == COMMENT || state == DQUOTE || state == SQUOTE))
			merge_tokens(&t, state);
		else if (t->next && t->type == LESS && t->next->type == LESS)
			merge_tokens(&t, DLESS);
		else if (t->next && t->type == GREAT && t->next->type == GREAT)
			merge_tokens(&t, DGREAT);
		else
			t = t->next;
	}
	if (state == SQUOTE || state == DQUOTE)
		return (1);
	return (0);
}

// Creates token list by splitting input line on metacharacters.
// metacharacters: |, <, >, ' ', '\t, '\n'.
// ignores  metacharacters: &, ;, (, ) (not part of the project scope)
void	split_to_list(char *str, char *delim, t_node **tokens)
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

// creates tokens for ther parser that have a token content and type
t_node	*lexer(char *input_line, char *delim)
{
	t_node	*tokens;

	tokens = NULL;
	split_to_list(input_line, delim, &tokens);
	if (check_split_tokens(tokens))
	{
		write(2, "Error: input: unclosed quotes\n", 30);
		lstclear(&tokens, delete_content);
		return (NULL);
	}
	return (tokens);
}
