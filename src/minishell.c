/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/23 12:52:30 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	t_node **tokens;
	tokens = malloc(sizeof(t_node **));
	if (!tokens)
		exit_error(21);
	*tokens = NULL;
	char *str = "Hello world>How| are$YOU?> today?";
	ft_lexer(tokens, str);
	
	while (*tokens)
	{
		printf("type=%d\tcontent=%s\n", (*tokens)->type, (char *)(*tokens)->content);
		*tokens = (*tokens)->next;
	}
	exit(EXIT_SUCCESS);
}
