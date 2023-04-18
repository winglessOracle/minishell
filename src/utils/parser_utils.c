/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/18 19:47:39 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd)
{
	if ((*token)->content)
	{
		lstadd_back(&cmd->cmd_argv, lstpop(token));
		cmd->cmd_argc++;
	}
	else
		remove_node(token, cmd);
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
	if ((*token && (*token)->content && !ft_isalpha((*token)->content[0]) 
		&& (*token)->content[0] != '_') || cmd->cmd_argc != 0)
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

int	expand_tilde(t_node **token, t_smpl_cmd *cmd)
{
	char	*temp;
	char	*home;

	(void)cmd;
	temp = (*token)->content;
	home = get_variable(cmd->env_list, "HOME");
	if (ft_strlen(temp) == 1)
	{
		if (home)
			(*token)->content = ft_strdup(home);
		else
		{
			return_error("minishell: HOME not set\n", 1);
			(*token)->content = NULL;
		}
	}
	else
		(*token)->content = ft_strjoin(home, &temp[1]);
	free(temp);
	free(home);
	return (0);
}
