/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 11:05:08 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	test_lexer(char *str, t_node *tokens)
{
	int i = 1;
	
	printf("\nprinting output list of lexer:\n\n");
	printf("tested string:\t\t%s\n", str);
	printf("tested deliminators:\t'|<> '\n\n"); // &;() skipped for now
	while (tokens)
	{
		// printf("--node [%d]--\ntype\t<%d>\ncontent\t_%s_\n\n", i, tokens->type, tokens->content);
		printf("token:\t%s\ntype:\t%d\n\n", tokens->content, tokens->type);
		tokens = tokens->next;
		i++;
	}
}

void	run_tests(char *str, t_node *tokens, t_master *master)
{
	if (tokens)
		test_lexer(str, tokens);
	print_env(master->env_list, 3);
	//test get variable
	printf("\ntest print get variable for PS1 and PS2\n");
	printf("\tPS1=%s\n", get_variable(master->env_list, "PS1"));
	printf("\tPS2=%s\n\n", get_variable(master->env_list, "PS2"));
}
