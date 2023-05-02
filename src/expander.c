/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/02 11:41:04 by ccaljouw      ########   odam.nl         */
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
	// print_tokens(*token, " in expand var\n");
	if ((*token)->content[0] == '?')
		str = ft_itoa(g_exit_status);
	else if ((*token)->content[0] == '\'' || (*token)->content[0] == '\"')
	{
		(*token)->type = check_token_content(*token, (*token)->type);
		// print_tokens(*token, " in expand var quoted\n");
		merge_quoted(token, cmd);
		str = ft_strdup((*token)->content);
	}
	else
	{
		str = get_variable(cmd->env_list, (*token)->content);
		// print_tokens(*token, " 2. in expand var\n");
	}
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
	// t_node	*temp;

	if (count_quotes((*token)->content, '\'') % 2 || count_quotes((*token)->content, '\'') % 2)
		merge_quoted(token, cmd);
	// printf("content in expand: %s\n", (*token)->content);
	words = split_to_list((*token)->content, "$=?/\'\".");
	free((*token)->content);
	(*token)->content = NULL;
	while (words)
	{
		// print_tokens(words, "in expand\n");
		if (words && words->content && words->content[0] == '$')
		{
			// printf("1. in expand content: %s, next: %s\n", words->content, words->next->content); 
			expand_var(&words, cmd);
			// print_tokens(words, "after expand var in expander\n");
	
			if (words->content)
				(*token)->content = ft_strjoin_free_s1((*token)->content, words->content);
			remove_node(&words, cmd);
			// printf("1. content: %s\n", content);
		}
		else if (words)
		{
			// printf("2. expand: words content: %s, type: %d, token type: %d\n", words->content, words->type, (*token)->type);
			if (words->content[0] == '\'' || words->content[0] == '\"')
			{
				words->type = check_token_content(words, (*token)->type);
				// print_tokens(*token, " in expand var quoted\n");
				merge_quoted(&words, cmd);
			}
			(*token)->content = ft_strjoin_free_s1((*token)->content, words->content);
			remove_node(&words, cmd);
		}
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

int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)  //expand word (make separate expander for redirects)
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
		// printf ("1. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
		(*token)->type = check_token_content(*token, (*token)->type);
		// printf ("2. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
		if ((*token)->type && (*token)->type > 8)
			state = parse[(*token)->type](token, cmd);
		if (state == -1)
			return (-1);
		else
			(*token)->type = state;
		// print_tokens(*token, "in expander after parse\n");
		if (*token && (*token)->type == WORD)
		{
			// printf("add to cmd: %s\n", (*token)->content);
			add_word_to_cmd(token, cmd);
			// print_cmd(cmd);
		}
	}
	return (0);
}