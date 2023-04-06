/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/06 13:24:40 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	get_redirect_type(t_node **tokens, t_smpl_cmd *cmd)
{
	int	type;

	type = 0;
	if (*tokens && (*tokens)->content[0] == '<')
		type = INPUT;
	else if (*tokens && (*tokens)->content[0] == '>')
		type = OUTPUT;
	remove_node(tokens, cmd);
	if (!*tokens)
		return (-1);
	if (type == INPUT && (*tokens)->content[0] == '<')
	{
		type = HEREDOC;
		remove_node(tokens, cmd);
	}
	else if (type == OUTPUT && (*tokens)->content[0] == '>')
	{
		type = APPEND;
		remove_node(tokens, cmd);
	}
	else if ((*tokens)->type == REDIRECT)
		type = -1;
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	return (type);
}

int	expand_redirect(t_node **tokens, t_smpl_cmd *cmd, int type)
{
	int				state;
	static function	*parse[6];
	
	state = 0;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	parse[EXPAND] = expand;
	while (*tokens)
	{
		state = check_token_content(*tokens, (*tokens)->type);
		if (state == WORD || state == ASSIGN || (state == EXPAND && type == HEREDOC))
			break;
		state = parse[state](tokens, cmd);
	}
	if (*tokens)
		(*tokens)->type = type;
	else
		state = syntax_error(tokens, cmd, "Redirect error\n");
	return (state);
}

int	get_redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	int	type;

	// printf("*REDIRECT* %s\n", (*tokens)->content);
	type = get_redirect_type(tokens, cmd);
	type = expand_redirect(tokens, cmd, type);
	if (type == -1)
		type = syntax_error(tokens, cmd, "Redirect error\n");
	else
		lstadd_back(&cmd->redirect, lstpop(tokens));
	print_tokens(cmd->redirect);
	return (type);
}
