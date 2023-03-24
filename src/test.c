/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/24 14:07:33 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	test_lexer(char *str, t_node **tokens)
{
	int i = 1;
	
	printf("\nprinting output list of lexer:\n\n");
	printf("tested string:\t\t%s\n", str);
	printf("tested deliminators:\t'|&;()<> '\n");

	while (*tokens)
	{
		printf("--node [%d]--\ntype\t<%d>\ncontent\t'%s'\n\n", i, (*tokens)->type, (char *)(*tokens)->content);
		*tokens = (*tokens)->next;
		i++;
	}
	
}

void	run_tests(char *str, t_node **tokens, t_master *master)
{
	test_lexer(str, tokens);
	print_env(master->env_list);
}