/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/11 12:22:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd)
{
	lstadd_back(&cmd->cmd_argv, lstpop(token));
	cmd->cmd_argc++;
	return (0);
}

int	remove_comment(t_node **token, t_smpl_cmd *cmd)
{
	while (*token && (*token)->type != NEW_LINE)
		remove_node(token, cmd);
	return (0);
}

int	parser_assign(t_node **token, t_smpl_cmd *cmd)
{
	if (cmd->cmd_argc != 0)
		return (add_word_to_cmd(token, cmd));
	lstadd_back(&cmd->assign, lstpop(token));
	remove_node(token, cmd);
	return (0);
}

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	if (*token && (*token)->type == PIPE)
	{
		if (!(*token)->next || (*token)->next->type == NEW_LINE)
			return (syntax_error(token, cmd, "no command after '|'\n", -1));
		remove_node(token, cmd);
	}
	if (cmd->cmd_argv == NULL && cmd->redirect == NULL && cmd->assign == NULL)
		return (syntax_error(token, cmd, "", -1));
	return (1);
}

int	remove_node(t_node **token, t_smpl_cmd *cmd)
{	
	t_node	*temp;
	int		state;

	(void)cmd;
	state = 0;
	if (!*token)
		return (-1);
	if ((*token)->type == NEW_LINE)
		state = 1;
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (state);
}
