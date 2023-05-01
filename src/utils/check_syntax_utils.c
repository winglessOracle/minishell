/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:40:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/01 14:03:21 by ccaljouw      ########   odam.nl         */
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
	// printf("in check token content: %s, type: %d\n", token->content, type);
	// printf("1. hier\n");
	if (str[0] == '#' && type != DQUOTE && type != SQUOTE)
		return (COMMENT);
	if (str[0] == '~' && (str[1] == '/' || str[1] == '\0'))
		return (TILDE);
	// printf("2. hier\n");
	while (str[i])
	{
		if (str[i] == '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
				&& type != SQUOTE)
		{
			// printf("return EXPAND\n");
			return (EXPAND);
		}
		i++;
	}
	i = 0;
	// printf("3. hier\n");
	// while (str[i])
	// {
	// 	i++;
	// }
	// printf("4. hier\n");
	if (check_assign(token->content, WORD))
		return (ASSIGN);
	return (WORD);
}

// int	check_sub_content(t_node *token, char quote, int open)
// {
// 	int		i;
// 	int		type;
// 	int		dquote;
// 	int		squote;
// 	char	*str;

// 	i = 0;
// 	dquote = 0;
// 	squote = 0;
// 	str = token->content;
// 	// printf("type in ceck sub content, content: %s, quote: %c, open: %d\n", str, quote, open);
// 	if (!open)
// 	{
// 		i = check_token_content(token, WORD);
// 		if ( i == COMMENT || i == ASSIGN || i == TILDE)
// 			i = WORD;
// 		return (i);
// 	}
// 	else if  (quote == '\"')
// 		type = DQUOTE;
// 	else
// 		type = SQUOTE;
// 	// printf ("type now: %d\n", type);
// 	if (!type)
// 		remove_double_quotes(&token);
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && type != SQUOTE)
// 		{
// 			dquote++;
// 			if (dquote == 2)
// 			return (DQUOTE);
// 		}
// 		if (str[i] == '\'' && type != DQUOTE)
// 		{
// 			squote++;
// 			if (squote == 2)	
// 				return (SQUOTE);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	// printf("type: %d, squote: %d, dquote: %d\n", type, squote, dquote);
// 	while (str[i] && type != SQUOTE && !squote)
// 	{
// 		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' \
// 			&& !(quote == '\''))
// 			return (EXPAND);
// 		i++;
// 	}
// 	return(WORD);
// }
