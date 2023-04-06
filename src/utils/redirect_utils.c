/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/06 10:20:41 by cariencaljo   ########   odam.nl         */
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

int	expand_redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	int				type;
	int				state;
	static function	*parse[6];
	
	type = (*tokens)->type;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	if (type == HEREDOC)
		parse[EXPAND] = NULL;
	else
		parse[EXPAND] = expand;
	
}

int	redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	int	type;

	// printf("*REDIRECT* %s\n", (*tokens)->content);
	type = get_redirect_type(tokens, cmd);
	if (*tokens && type != -1)
	{
		(*tokens)->type = type;
		lstadd_back(&cmd->redirect, lstpop(tokens));
		type = 0;
	}
	else
	{
		write(2, "Redirect error\n", 15);
		type = -1;
	}
	print_tokens(cmd->redirect);
	return (type);
}
