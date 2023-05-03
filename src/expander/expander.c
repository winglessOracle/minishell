/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/03 19:12:12 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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
		else if (*token && (*token)->type > 8)
			(*token)->type = state;
		if (*token && (*token)->type == WORD)
			add_word_to_cmd(token, cmd);
	}
	return (0);
}
