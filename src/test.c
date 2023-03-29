/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 15:57:25 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");	
}

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

void	run_tests(t_smpl_cmd *cmd, t_node *env_list)
{
	while (cmd->cmd_var)
	{
		printf("%s\n", cmd->cmd_var->content);
		cmd->cmd_var = cmd->cmd_var->next;
	}
	// print_env(env_list, 3);
}