/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 18:02:28 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (cmd && cmd->cmd_argv)
	{
		printf("type: %d, \tcontent: %s\n", cmd->cmd_argv->type, cmd->cmd_argv->content);
		cmd->cmd_argv = cmd->cmd_argv->next;
	}
}

void	print_pipeline(t_pipe *pipe)
{
	int	i;

	i = 1;
	if (pipe && pipe->pipe_argv)
	{
		while (pipe->pipe_argv)
		{
			printf("--------------------------------\n\tCMD %i: %s\n\tARGS: %d\n--------------------------------\n", i, pipe->pipe_argv->cmd_argv->content, pipe->pipe_argv->cmd_argc);
			print_cmd(pipe->pipe_argv);
			pipe->pipe_argv = pipe->pipe_argv->next;
			i++;
			printf("--------------------------------\n\n");
		}
	}
}

//flags: 1 = local (default) 2 = external 3 = all
void	print_env(t_node *env_list, int flag)
{
	while (env_list)
	{
		if (flag == 1)
		{
			if (env_list->type == 1)
				printf("%s\n", env_list->content);
		}
		if (flag == 2)
		{
			if (env_list->type == 2)  // also prevent printing when var=NULL
				printf("%s\n", env_list->content);
		}
		if (flag == 3)
		 	if (env_list->type == 1 || env_list->type == 2)
				printf("%s\n", env_list->content);		
		env_list = env_list->next;
	}
}