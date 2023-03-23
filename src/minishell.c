/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/23 18:55:43 by carlo         ########   odam.nl         */
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
	char *str = "Hello world>>How| are$YOU|> to||day?";
	ft_lexer(tokens, str);
	
		
	//test print
	printf("\nprinting output list of lexer:\n\n");
	printf("tested string:\t\t%s\n", str);
	printf("tested deliminators:\t'>|'\n\n");
	
	int i = 1;
	while (*tokens)
	{
		printf("--node [%d]--\ntype\t<%d>\ncontent\t'%s'\n\n", i, (*tokens)->type, (char *)(*tokens)->content);
		*tokens = (*tokens)->next;
		i++;
	}
	exit(EXIT_SUCCESS);
}
