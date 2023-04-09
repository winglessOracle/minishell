/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/09 17:17:05 by cariencaljo   ########   odam.nl         */
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

int	get_redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	int	type;

	// printf("*REDIRECT* %s\n", (*tokens)->content);
	type = get_redirect_type(tokens, cmd);
	if (type == -1)
		return (syntax_error(tokens, cmd, "Redirect error\n", -1));
	type = expand_redirect(tokens, cmd, type);
	print_tokens(cmd->redirect, "REDIRECT");
	if (type != -1)
		type = 0;
	return (syntax_error(tokens, cmd, "Redirect error\n", type));
}
