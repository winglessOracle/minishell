/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/29 13:21:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	expand_var(t_node **token, t_smpl_cmd *cmd)
{
	char	*str;

	remove_node(token, cmd);
	if ((*token)->content[0] == '?')
		str = ft_itoa(g_exit_status);
	else if ((*token)->content[0] == '\'' || (*token)->content[0] == '\"')
	{
		// split_and_remove_quotes(token, cmd);
		str = ft_strdup((*token)->content);		
	}
	else
		str = get_variable(cmd->env_list, (*token)->content);
	free((*token)->content);
	(*token)->content = str;
	return (0);
}

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

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;

	words = split_to_list((*token)->content, "$=?/\"\'");
	remove_node(token, cmd);
	while (words && words->next)
	{
		if (words->content && words->content[0] == '$')
			expand_var(&words, cmd);
		else if (words->next->next && words->next->content \
							&& words->next->content[0] == '$')
			expand_var(&words->next, cmd);
		else if (!words->content)
			remove_node(&words, cmd);
		else if (words->next && !words->next->content)
			remove_node(&words->next, cmd);
		else if (words && words->next)
			merge_tokens(words, WORD);
	}
	if (words && words->content)
		temp = split_expanded(words, cmd);
	else
		temp = words;
	lstinsert_lst(token, temp);
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

int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)  //expand word (make separate expander for redirects)
{
	static t_function	*parse[16];
	int					state;

	(void)list;
	state = 0;
	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	parse[TILDE] = expand_tilde;
	while (*token && (*token)->type == WORD && !state)
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		// printf ("in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
		state = parse[(*token)->type](token, cmd);
		if (*token && (*token)->type == WORD)
			add_word_to_cmd(token, cmd);
	}
	return (state);
}