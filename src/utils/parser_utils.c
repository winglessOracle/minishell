/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 13:01:48 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// int		todo(t_node **token, t_smpl_cmd *cmd)
// {
// 	printf("not handeled yet: type: %d, content: %s\n", (*token)->type, (*token)->content);
// 	// (*token) = (*token)->next;
// 	// remove_node(token, cmd);
// 	return (0);
// }

// int	set_type_word(t_node **token, t_smpl_cmd *cmd)
// {
// 	if (cmd->cmd_argc == 0)
// 		(*token)->type = NAME;
// 	else
// 		(*token)->type = WORD;
// 	return (0);
// }

int	check_token_content(t_node *token, int type)
{
	char	*str;
	int		i;

	i = 0;
	str = token->content;
	if (str[0] == '#' && type != DQUOTE && type != SQUOTE)
		return (COMMENT);
	while (str[i])
	{
		if (str[i]== '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		else if (str[i] == '$' && type != SQUOTE)
			return (EXPAND);
		else if (str[i] == '=' && type != DQUOTE && type != SQUOTE)
			return (ASSIGN);
		i++;
	}
	return (WORD);
}
