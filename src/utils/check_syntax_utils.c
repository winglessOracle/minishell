/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:40:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 19:49:16 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	check_assign(char *str, int type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && type != DQUOTE && type != SQUOTE)
			return (ASSIGN);
		i++;
	}
	return (WORD);
}

int	check_token_content(t_node *token, int type)
{
	char	*str;
	int		i;

	i = 0;
	if (!token->content)
		return (WORD);
	str = token->content;
	if (str[0] == '#' && type != DQUOTE && type != SQUOTE)
		return (COMMENT);
	if (str[0] == '~' && (str[1] == '/' || str[1] == '\0'))
		return (TILDE);
	while (str[i])
	{
		if (str[i] == '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
				&& type != SQUOTE)
			return (EXPAND);
		i++;
	}
	if (check_assign(token->content, WORD))
		return (ASSIGN);
	return (WORD);
}

int	check_sub_content(t_node *token, char quote, int open)
{
	int		i;
	int		type;
	char	*str;

	i = 0;
	str = token->content;
	// printf("type in ceck sub content, content: %s, quote: %c, open: %d\n", str, quote, open);
	if (!open)
		type = check_token_content(token, WORD);
	else if  (quote == '\"')
		type = DQUOTE;
	else
		type = SQUOTE;
	while (str[i])
	{
		if (str[i] == '\"' && type != SQUOTE)
			return (DQUOTE);
		if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
			&& !(quote == '\'' && type != SQUOTE))
			return (EXPAND);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
			&& !(quote == '\'' && type != SQUOTE))
			return (EXPAND);
		i++;
	}
	return(WORD);
}
