/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 12:54:15 by cariencaljo   ########   odam.nl         */
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
	// printf("IN: %s, OUT: %s, ERR: %s\n", cmd->infile, cmd->outfile, cmd->errfile);
	// printf("Here_end: %s\tAppend: %d\n-------------------------------------\n", cmd->here_end, cmd->append);
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
			printf("-------------------------------------\n\tCMD %i:", i);
			if (pipe->pipe_argv->cmd_argv)
				printf("\t%s\n\tARGS:\t%d\n-------------------------------------\n",pipe->pipe_argv->cmd_argv->content, pipe->pipe_argv->cmd_argc);
			else
				printf("\n");
			print_cmd(pipe->pipe_argv);
			pipe->pipe_argv = pipe->pipe_argv->next;
			i++;
			printf("-------------------------------------\n\n");
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
			if (env_list->type == 1 && check_env_content(env_list->content))
				printf("%s\n", env_list->content);
		}
		if (flag == 2)
		{
			if (env_list->type == 2 && check_env_content(env_list->content))
				printf("%s\n", env_list->content);
		}
		if (flag == 3)
			if ((env_list->type == 1 || env_list->type == 2)
				&& check_env_content(env_list->content))
				printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}