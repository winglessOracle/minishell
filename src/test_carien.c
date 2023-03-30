/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_carien.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 11:54:11 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");	
}

void	print_tokens(t_node *tokens)
{
	int i = 1;
	
	printf("--------------------------------\n\t     TOKENS\n--------------------------------\n");
	while (tokens)
	{
		printf("type: %d \tcontent: %s\n", tokens->type, tokens->content);
		tokens = tokens->next;
		i++;
	}
	printf("--------------------------------\n\n");
}

void	print_cmd(t_smpl_cmd *cmd)
{
	printf("--------------------------------\n\tCMD : %s\n\tARGS: %d\n--------------------------------\n", cmd->cmd_argv->content, cmd->cmd_argc);
	while (cmd->cmd_argv)
	{
		printf("%s\n", cmd->cmd_argv->content);
		cmd->cmd_argv = cmd->cmd_argv->next;
	}
	printf("--------------------------------\n\n");
}

void	print_pipeline(t_pipe *pipe)
{
	while (pipe->pipe_argv)
	{
		printf("--------------------------------\n\tCMD : %s\n\tARGS: %d\n--------------------------------\n", pipe->pipe_argv->cmd_argv->content, pipe->pipe_argv->cmd_argc);
		while (pipe->pipe_argv->cmd_argv)
		{
			printf("%s\n", pipe->pipe_argv->cmd_argv->content);
			pipe->pipe_argv->cmd_argv = pipe->pipe_argv->cmd_argv->next;
		}
		printf("--------------------------------\n\n");
		pipe->pipe_argv = pipe->pipe_argv->next;
	}
}