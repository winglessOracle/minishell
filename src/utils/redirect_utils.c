/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 22:05:59 by cariencaljo   ########   odam.nl         */
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
	// int					type;
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
	(*tokens)->type = check_token_content(*tokens, WORD);
	// print_tokens(*tokens, "in redirect\n");
	if ((*tokens)->type == COMMENT)
		(*tokens)->type = parse[(*tokens)->type](tokens, cmd);
	while (*tokens && (*tokens)->type == BLANK)
		remove_node(tokens, cmd);
	(*tokens)->type = check_token_content(*tokens, WORD);
	if (((*tokens)->content[0] == '|' || (*tokens)->content[0] == '&') && state != OUTPUT)
		return (syntax_error(tokens, cmd, "Redirect syntax error\n", -1));
	if (((*tokens)->content[0] == '|' || (*tokens)->content[0] == '&') && state == OUTPUT)
	{
		remove_node(tokens, cmd);
		while ((*tokens)->type != WORD)
			remove_node(tokens, cmd);
		// print_tokens(*tokens, "after remove pipe\n");
	}
	if ((*tokens)->type != WORD)
		(*tokens)->type = parse[(*tokens)->type](tokens, cmd);
	// printf("2. content: %s, type: %d, redirect type: %d\n", (*tokens)->content, (*tokens)->type, state);
	(*tokens)->type = state;
	lstadd_back(&cmd->redirect, lstpop(tokens));
	return (0);
}
