/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/02 19:11:52 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*split_expanded(t_node *words, t_smpl_cmd *cmd)
{
	t_node	*temp;
	char	*str;

	temp = NULL;
	if (words)
	{
		temp = words;
		str = get_variable(cmd->env_list, "IFS");
		if (!str)
			str = ft_strdup(" ");
		words = split_to_list(temp->content, str);
		remove_node(&temp, cmd);
		free(str);
		lstinsert_lst(&temp, words);
	}
	return (temp);
}

int	expand_var(t_node **token, t_smpl_cmd *cmd)
{
	char	*str;

	remove_node(token, cmd);
	if ((*token)->content[0] == '?')
		str = ft_itoa(g_exit_status);
	else if ((*token)->content[0] == '\'' || (*token)->content[0] == '\"')
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		merge_quoted(token, cmd);
		str = ft_strdup((*token)->content);
	}
	else
		str = get_variable(cmd->env_list, (*token)->content);
	if (*token)
	{
		free((*token)->content);
		(*token)->content = str;
	}
	return (0);
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;
	t_node	*last;
	char	*str;

	if (count_quotes((*token)->content, '\'') % 2 || count_quotes((*token)->content, '\'') % 2)
		merge_quoted(token, cmd);
	words = split_to_list((*token)->content, "$=?/\'\".");
	temp = *token;
	free((*token)->content);
	(*token)->content = NULL;
	while (words)
	{
		if (words && words->content && words->content[0] == '$' && words->next)
		{
			expand_var(&words, cmd);
			if (words->content)
				(*token)->content = ft_strjoin_free_s1((*token)->content, words->content);
			remove_node(&words, cmd);
			if ((*token)->content)
			{
				str = get_variable(cmd->env_list, "IFS");
				if (str)
				{
					temp = split_to_list((*token)->content, str);
					last = lstlast(temp);
					remove_node(token, cmd);
					lstinsert_lst(token, temp);
					temp = *token;
					*token = last;
					free(str);
				}
			}
		}
		else if (words)
		{
			if (words->content[0] == '\'' || words->content[0] == '\"')
			{
				words->type = check_token_content(words, (*token)->type);
				merge_quoted(&words, cmd);
			}
			(*token)->content = ft_strjoin_free_s1((*token)->content, words->content);
			remove_node(&words, cmd);
		}
		*token = temp;
	}
	return (0);
}

int	expand_sub(t_node **token, t_smpl_cmd *cmd)
{
	static t_function	*parse[13];

	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	(*token)->type = parse[(*token)->type](token, cmd);
	return ((*token)->type);
}

int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)
{
	static t_function	*parse[16];
	int					state;

	(void)list;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	parse[TILDE] = expand_tilde;
	state = 0;
	while (*token && ((*token)->type == WORD || (*token)->type > 8))
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		if ((*token)->type && (*token)->type > 8)
			state = parse[(*token)->type](token, cmd);
		if (state == -1)
			return (-1);
		else if (*token)
			(*token)->type = state;
		if (*token && (*token)->type == WORD)
			add_word_to_cmd(token, cmd);
	}
	return (0);
}
