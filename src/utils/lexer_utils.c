/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 09:23:02 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/29 10:10:50 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

// merges provided node with the next node and set provided type for merged node
void	merge_tokens(t_node **token, int type)
{
	char	*content;

	if ((*token)->next)
	{
		content = ft_strjoin((*token)->content, (*token)->next->content);
		lstdelone(lstpop(token), delete_content);
		free((*token)->content);
		(*token)->content = content;
		(*token)->type = type;
	}
}

int	get_state(char *str)
{
	int		state;

	state = 0;
	if (*str == '#')
		return (COMMENT);
	while (*str)
	{
		if (*str == 34 && state == 0)
			state = DQUOTE;
		else if (*str == 39 && state == 0)
			state = SQUOTE;
		else if (*str == 34 && state == DQUOTE)
			state = 0;
		else if (*str == 39 && state == SQUOTE)
			state = 0;
		else if (*str == 36 && state != SQUOTE)
			state = EXPAND;
		else if (*str == 61 && state == 0)
			state = ASSIGN;
		str++;
	}
	return (state);
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
