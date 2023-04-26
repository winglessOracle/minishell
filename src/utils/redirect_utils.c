/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/25 21:36:11 by cariencaljo   ########   odam.nl         */
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
	int					type;
	static t_function	*parse[16];

	(void)list;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_quotes;
	parse[DQUOTE] = remove_quotes;
	parse[EXPAND] = expand;
	parse[TILDE] = expand_tilde;
	state = get_redirect_type(tokens, cmd);
	if (state == -1)
		return (syntax_error(tokens, cmd, "Redirect\n", -1));
	type = check_token_content(*tokens, WORD);
	if (type == COMMENT)
		type = parse[type](tokens, cmd);
	if (!*tokens || (*tokens)->type == PIPE_END)
		return (syntax_error(tokens, cmd, "Redirect\n", -1));
	type = check_token_content(*tokens, WORD);
	(*tokens)->type = state;
	if (type != WORD && type != ASSIGN && !(state == HEREDOC && type == EXPAND))
		type = parse[type](tokens, cmd);
	lstadd_back(&cmd->redirect, lstpop(tokens));
	return (syntax_error(tokens, cmd, "Redirect\n", type));
}
