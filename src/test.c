/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/27 18:22:05 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	test_lexer(t_node **tokens) //error with empty string
{
	int i = 1;
	
	printf("\nprinting output list of lexer:\n\n");
	printf("tested deliminators:\t'|&;()<> '\n");

	while (*tokens)
	{
		printf("--node [%d]--\ntype\t<%d>\ncontent\t'%s'\n\n", i, (*tokens)->type, (char *)(*tokens)->content);
		*tokens = (*tokens)->next;
		i++;
	}
}

void	run_tests(t_node **tokens, t_master *master)
{
	test_lexer(tokens);
	print_env(&master->env_list, 2);
	printf("test=%s", get_var(&master->env_list, "PAGER"));
}
