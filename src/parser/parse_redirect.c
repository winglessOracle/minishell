/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/11 15:16:57 by cariencaljo   ########   odam.nl         */
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
	if (type == OUTPUT && (*tokens)->content[0] == '|')
		remove_node(tokens, cmd);
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	if (*tokens && (*tokens)->type == REDIRECT)
		type = type_current_remove_next(-1, tokens, cmd);
	else if (!*tokens)
		type = -1;
	return (type);
}

int	get_redirect(t_node **tokens, t_smpl_cmd *cmd, int state)
{
	static t_function	*parse[16];

	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[TILDE] = expand_tilde;
	if (*tokens)
	{
		(*tokens)->type = check_token_content(*tokens, WORD);
		if ((*tokens)->type == DQUOTE && state == HEREDOCQ)
			merge_quoted_heredoc(tokens, cmd, 1);
		else if ((*tokens)->type != WORD && !(state == HEREDOC \
										&& (*tokens)->type == EXPAND))
			parse[(*tokens)->type](tokens, cmd);
		if (*tokens)
		{
			(*tokens)->type = state;
			replace_wildcards((*tokens)->content, 26, '*');
			lstadd_back(&cmd->redirect, lstpop(tokens));
			return (0);
		}
	}
	return (syntax_error(tokens, cmd, "Redirect syntax error\n", -1));
}

int	redirect_tokens(t_node **tokens, t_smpl_cmd *cmd, t_list *list)
{
	int					state;

	(void)list;
	state = get_redirect_type(tokens, cmd);
	if (state == -1 || ((*tokens)->type == PIPE_END \
						|| (*tokens)->type == AND || (*tokens)->type == OR))
		return (syntax_error(tokens, cmd, "Redirect syntax error\n", -1));
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	(*tokens)->type = check_token_content(*tokens, WORD);
	if (state == HEREDOC && ((*tokens)->type == SQUOTE \
									|| (*tokens)->type == DQUOTE))
		state = HEREDOCQ;
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	return (get_redirect(tokens, cmd, state));
}
