/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/08 15:26:01 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*expand_word(t_node *token, t_smpl_cmd *cmd)
{
	char	*str;
	
	print_tokens(token, "EXPAND WORD");
	remove_node(&token, cmd);
	print_tokens(token, "EXPAND WORD 2");
	str = get_variable(cmd->env_list, (token)->content);
	printf("str: %s\n", str);
	if (!str)
		remove_node(&token, cmd);
	else
	{
		free((token)->content);
		(token)->content = str;
	}
	print_tokens(token, "EXPAND WORD END");
	return (token);
}

int	expand(t_node **token, t_smpl_cmd *cmd)
{
	t_node	*words;
	t_node	*temp;
	
	words = split_to_list((*token)->content, "$");
	temp = words;
	remove_node(token, cmd);
	if (temp && temp->next)
	{
		print_tokens(temp, "EXPAND");
		if (temp->content[0] == '$')
			temp = expand_word(temp, cmd);
		else if (temp->next->content[0] == '$')
			temp->next = expand_word(temp->next, cmd);
		print_tokens(temp, "EXPAND 2");
		while (temp->next)
			merge_tokens(temp, WORD);
		print_tokens(temp, "EXPAND END LOOP");
	}
	lstinsert_lst(token, temp);
	return (0);
}

int	expander(t_node **token, t_smpl_cmd *cmd)
{
	int					state;
	static t_function	*parse[10];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	// printf("*CHECK CONTENT* %s\n", (*token)->content);
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		print_tokens(*token, "EXPANDER");
		state = parse[state](token, cmd);
	}
	return (state);
}
