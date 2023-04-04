/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/04 12:49:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	test_lexer(t_node **tokens)
{
	int i = 1;
	t_node	*temp;
	
	printf("\nprinting output list of lexer:\n\n"); // error with NULL input
	printf("tested deliminators:\t'|<> '\n"); // &;() skipped for now (tab?)
	temp = *tokens;
	while (temp)
	{
		printf("--node [%d]--\ntype\t<%d>\ncontent\t_%s_\n\n", i, temp->type, (char *)temp->content);
		// printf("token: %s, type: %d\n", (char *)(*tokens)->content, (*tokens)->type);
		temp = temp->next;
		i++;
	}
}

void	run_tests(t_node **tokens, t_master *master)
{
	print_env(&master->env_list, 3);
	get_variable(&master->env_list, NULL);
	//test_lexer(tokens);
}

