/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/20 12:05:49 by cariencaljo   ########   odam.nl         */
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
			str=ft_strdup(" ");
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

	words = split_to_list((*token)->content, "$=?");
	remove_node(token, cmd);
	while (words && words->next)
	{
		if (!words->content)
			remove_node(&words, cmd);
		if (words->content[0] == '$')
			expand_var(&words, cmd);
		else if (words->next->content[0] == '$')
			expand_var(&words->next, cmd);
		else if (words && words->next)
			merge_tokens(words, WORD);
	}
	if (words && words->content)
	{
		temp = split_expanded(words, cmd);
		lstinsert_lst(token, temp);
	}
	else
		lstinsert_lst(token, words);
	return (0);
}

int	expander(t_node **token, t_smpl_cmd *cmd)
{
	int					state;
	static t_function	*parse[11];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_quotes;
	parse[DQUOTE] = remove_quotes;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	parse[TILDE] = expand_tilde;
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		state = parse[state](token, cmd);
	}
	return (state);
}
