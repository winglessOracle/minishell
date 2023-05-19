/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 19:20:31 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/19 10:40:27 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*split_expanded(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*temp;
	t_node	*last;
	char	*str;

	temp = NULL;
	str = get_variable(cmd->env_list, "IFS");
	if (str)
	{
		temp = split_to_list_expand((*token)->content, str);
		last = lstlast(temp);
		remove_node(token, cmd);
		lstinsert_lst(token, temp);
		temp = *token;
		*token = last;
		free(str);
	}
	return (temp);
}

char	*quoted_expand(t_node **token, t_smpl_cmd *cmd, char *str)
{
	if (!ft_strcmp((*token)->content, (*token)->next->content))
	{
		remove_node(token, cmd);
		str = ft_strdup("");
	}
	else
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		merge_quoted(token, cmd);
		str = ft_strdup((*token)->content);
	}
	return (str);
}

int	expand_var(t_node **token, t_smpl_cmd *cmd)
{
	char	*str;

	str = NULL;
	remove_node(token, cmd);
	if ((*token)->content[0] == '?')
		str = ft_itoa(g_exit_status);
	else if ((*token)->content[0] == '\'' || (*token)->content[0] == '\"')
		str = quoted_expand(token, cmd, str);
	else
		str = get_variable(cmd->env_list, (*token)->content);
	if (*token)
	{
		free((*token)->content);
		(*token)->content = str;
	}
	return (0);
}

t_node	*exp_spl(t_node **words, t_node **token, t_smpl_cmd *cmd, t_node *temp)
{
	expand_var(words, cmd);
	if ((*words)->content)
		(*token)->content = ft_strjoin_free_s1((*token)->content, \
													(*words)->content);
	remove_node(words, cmd);
	if ((*token)->content && ft_strlen((*token)->content) > 1)
		temp = split_expanded(token, cmd);
	return (temp);
}

void	add_after_var(t_node **words, t_node **token, t_smpl_cmd *cmd)
{
	if ((*words)->content[0] == '\'' || (*words)->content[0] == '\"')
	{
		(*words)->type = check_token_content(*words, (*token)->type);
		merge_quoted(words, cmd);
	}
	(*token)->content = ft_strjoin_free_s1((*token)->content, \
													(*words)->content);
	remove_node(words, cmd);
}
