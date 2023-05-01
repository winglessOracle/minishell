/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_new.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/07 21:51:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/05/01 13:44:35 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	expander(t_node **token, t_smpl_cmd *cmd, t_list *list)  //expand word (make separate expander for redirects)
{
	static t_function	*parse[16];

	(void)list;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = merge_quoted;
	parse[DQUOTE] = merge_quoted;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign;
	parse[TILDE] = expand_tilde;
	while (*token && ((*token)->type == WORD || (*token)->type > 8))
	{
		// printf ("1. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
		// remove_double_quotes(token);
		(*token)->type = check_token_content(*token, (*token)->type);
		// printf ("2. in expander, content: %s, type: %d\n", (*token)->content, (*token)->type);
		if ((*token)->type && (*token)->type > 8)
			(*token)->type = parse[(*token)->type](token, cmd);
		// printf ("3. after expander content: %s, type: %d\n", (*token)->content, (*token)->type);
		if (*token && (*token)->type == WORD)
		{
			// printf("add to cmd: %s\n", (*token)->content);
			add_word_to_cmd(token, cmd);
			// print_cmd(cmd);
		}
	}
	if (*token && (*token)->type == -1)
		return (-1);
	return (0);
}