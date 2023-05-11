/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:40:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 15:39:06 by cariencaljo   ########   odam.nl         */
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

void	replace_wildcards(char	*str, char replace, char with)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (!BONUS)
		return ;
	while (str[i])
	{
		if (str[i] == '\'' && !type)
			type = SQUOTE;
		else if (str[i] == '\'' && type == SQUOTE)
			type = 0;
		else if (str[i] == '\"' && !type)
			type = DQUOTE;
		else if (str[i] == '\"' && type == DQUOTE)
			type = 0;
		else if (str[i] == replace && type != SQUOTE && type != DQUOTE)
			str[i] = with;
		i++;
	}
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
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
				&& type != SQUOTE)
			return (EXPAND);
		i++;
	}
	if (check_assign(token->content, WORD))
		return (ASSIGN);
	return (WORD);
}
