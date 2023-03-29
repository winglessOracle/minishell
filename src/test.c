/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 22:31:01 by cariencaljo   ########   odam.nl         */
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

void	print_cmd(t_smpl_cmd *cmd)
{
	printf("\n----------------------\ncmd: %s,\t%d args\n----------------------\n", cmd->cmd_argv->content, cmd->cmd_argc);
	while (cmd->cmd_argv)
	{
		printf("%s\n", cmd->cmd_argv->content);
		cmd->cmd_argv = cmd->cmd_argv->next;
	}
	printf("----------------------\n");
}
