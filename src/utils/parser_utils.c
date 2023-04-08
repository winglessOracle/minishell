/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/08 09:38:15 by cariencaljo   ########   odam.nl         */
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
	int	check;

	check = check_pipe(*token, cmd);
	if ((*token)->type == PIPE)
		remove_node(token, cmd);
	return (check);
}