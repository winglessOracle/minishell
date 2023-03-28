/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/28 09:27:51 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
void	test_lexer(t_node **tokens) //error with empty string //error with double meta
{
	int i = 1;
	t_node	*temp;
	
	printf("\nprinting output list of lexer:\n\n");
	printf("tested string:\t\t%s\n", str);
	printf("tested deliminators:\t'|<> '\n"); // &;() skipped for now
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
	test_lexer(tokens);
	print_env(&master->env_list, 3);
	//printf("\nget var USER test=%s", get_variable(&master->env_list, "USER"));
}
