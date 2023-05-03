/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/03 10:15:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	type_current_remove_next(int type, t_node **tokens, t_smpl_cmd *cmd)
{
	remove_node(tokens, cmd);
	return (type);
}

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
		type = type_current_remove_next(HEREDOC, tokens, cmd);
	else if (type == OUTPUT && (*tokens)->content[0] == '>')
		type = type_current_remove_next(APPEND, tokens, cmd);
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	if (*tokens && (*tokens)->type == REDIRECT)
		type = type_current_remove_next(-1, tokens, cmd);
	else if (!*tokens)
		type = -1;
	return (type);
}

int	redirect_tokens(t_node **tokens, t_smpl_cmd *cmd, t_list *list)
{
	int					state;
	static t_function	*parse[16];

	(void)list;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[TILDE] = expand_tilde;
	state = get_redirect_type(tokens, cmd);
	if (state == -1)
		return (syntax_error(tokens, cmd, "Redirect syntax error\n", -1));
	if ((*tokens)->type == PIPE_END || (*tokens)->type == AND || (*tokens)->type == OR)
			return (syntax_error(tokens, cmd, "Redirect syntax error\n", -1));
	(*tokens)->type = check_token_content(*tokens, WORD);
	if (state == HEREDOC && ((*tokens)->type == SQUOTE || (*tokens)->type == DQUOTE))
		state = HEREDOCQ;
	if ((*tokens)->type == COMMENT)
		(*tokens)->type = parse[(*tokens)->type](tokens, cmd);
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	if (*tokens)
	{
		(*tokens)->type = check_token_content(*tokens, WORD);
		if ((*tokens)->type != WORD)
			(*tokens)->type = parse[(*tokens)->type](tokens, cmd);
		(*tokens)->type = state;
		lstadd_back(&cmd->redirect, lstpop(tokens));
	}
	return (0);
}
