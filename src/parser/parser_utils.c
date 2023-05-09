/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/03 11:56:12 by ccaljouw      ########   odam.nl         */
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
	while (*token && ft_strcmp((*token)->content, "\n"))
		remove_node(token, cmd);
	return (0);
}

int	parser_assign(t_node **token, t_smpl_cmd *cmd)
{
	int	check;

	check = 0;
	if (!cmd->cmd_argc)
	{
		check = check_valid_identifier((*token)->content);
		if (check)
			return (0);
		lstadd_back(&cmd->assign, lstpop(token));
		remove_node(token, cmd);
	}
	return (0);
}

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	(void)list;
	if (*token && !ft_strncmp((*token)->content, "|", 1))
	{
		remove_node(token, cmd);
		if (!(*token) || !ft_strncmp((*token)->content, "|", 1))
			return (syntax_error(token, cmd, "no command after '|'\n", -1));
		if (cmd->cmd_argv == NULL && cmd->redirect == NULL \
													&& cmd->assign == NULL)
			return (syntax_error(token, cmd, "syntax error\n", -1));
	}
	if (*token && (!ft_strcmp((*token)->content, ";") || !ft_strcmp((*token)->content, "&") || !ft_strcmp((*token)->content, "&&")))
	{
		if (cmd->cmd_argv == NULL && cmd->redirect == NULL \
													&& cmd->assign == NULL)
			return (syntax_error(token, cmd, "syntax error\n", -1));
	}
	return (1);
}

int	expand_tilde(t_node **token, t_smpl_cmd *cmd)
{
	char	*temp;
	char	*home;

	(void)cmd;
	temp = (*token)->content;
	home = get_variable(cmd->env_list, "~");
	if (!home)
	{
		remove_node(token, cmd);
		return (return_error("minishell: expand tilde: '~' not set", 1));
	}
	if (ft_strlen(temp) == 1)
		(*token)->content = ft_strdup(home);
	else
		(*token)->content = ft_strjoin(home, &temp[1]);
	(*token)->type = WORD;
	free(temp);
	free(home);
	return (0);
}