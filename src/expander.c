/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/01 14:01:57 by ccaljouw      ########   odam.nl         */
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
		merge_quoted(token, cmd);
		str = ft_strdup((*token)->content);
		printf("string: %s\n", str);	
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
	// t_node	*temp;
	char	*content;

	content = NULL;
	words = split_to_list((*token)->content, "$=?/\'\"");
	while (words)
	{
		// print_tokens(words, "in expand\n");
		// printf("in expand content: %s, next: %s\n", words->content, words->next->content); 
		if (words->content && words->content[0] == '$')
		{
			// printf("words type: %d\n", words->type);
			expand_var(&words, cmd);
			if (words->content)
				content = ft_strdup(words->content);
			remove_node(&words, cmd);
			// printf("1. content: %s\n", content);
		}
		else
		{
			words->type = check_token_content(words, (*token)->type);
			// printf("expand: words content: %s, content: %s, type: %d, token type: %d\n", words->content, content, words->type, (*token)->type);
			if (words->type == SQUOTE || words->type == DQUOTE)
				expand_sub(&words, cmd);
			// printf("expand: words content: %s, content: %s, type: %d, token type: %d\n", words->content, content, words->type, (*token)->type);	
			if (words->content)
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
			// printf("1. content: %s\n", content);
		}
	}
	free((*token)->content);
	(*token)->content = content;
	// if (words && words->content)
	// 	temp = split_expanded(words, cmd);
	// else
	// 	temp = words;
	// lstinsert_lst(token, temp);
	// printf("in expand content: %s\n", (*token)->content);
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

// int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)  //expand word (make separate expander for redirects)
// {
// 	static t_function	*parse[16];
// 	int					state;

// 	(void)list;
// 	state = 0;
// 	parse[WORD] = add_word_to_cmd;
// 	parse[COMMENT] = remove_comment;
// 	parse[SQUOTE] = merge_quoted;
// 	parse[DQUOTE] = merge_quoted;
// 	parse[EXPAND] = expand;
// 	parse[ASSIGN] = parser_assign;
// 	parse[TILDE] = expand_tilde;
// 	while (*token && (*token)->type == WORD && !state)
// 	{
// 		// printf ("1. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
// 		remove_double_quotes(token);
// 		(*token)->type = check_token_content(*token, (*token)->type);
// 		// printf ("2. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
// 		state = parse[(*token)->type](token, cmd);
// 		// printf ("3. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
// 		if (*token && (*token)->type == WORD)
// 		{
// 			// printf("add to cmd: %s\n", (*token)->content);
// 			add_word_to_cmd(token, cmd);
// 			// print_cmd(cmd);
// 		}
// 	}
// 	return (state);
// }