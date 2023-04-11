/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:08:03 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/11 14:50:32 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_node *tokens, char *str)
{
	int		i;

	i = 1;
	printf("--------------------------------\n\
			\t     %s\n--------------------------------\n", str);
	while (tokens)
	{
		printf("type: %2d\tnext: %11p\tcontent: --%s--\n", \
					tokens->type, tokens->next, tokens->content);
		tokens = tokens->next;
		i++;
	}
	printf("--------------------------------\n\n");
}

void	print_cmd(t_smpl_cmd *cmd)
{
	t_node	*temp;

	if (cmd)
		temp = cmd->cmd_argv;
	else
		return ;
	while (temp)
	{
		printf("type: %d, \tcontent: %s\n", temp->type, temp->content);
		temp = temp->next;
	}
}

void	print_pipeline(t_pipe *pipe)
{
	int			i;
	t_smpl_cmd	*temp;

	i = 1;
	if (pipe)
		temp = pipe->pipe_argv;
	else
		return ;
	if (temp)
	{
		while (temp)
		{
			printf("-------------------------------------\n\tCMD %i:", i);
			if (temp->cmd_argv)
				printf("\t%s\n\tARGS:\t%d\n-------------------------------------\
					\n", temp->cmd_argv->content, temp->cmd_argc);
			else
				printf("\n");
			print_cmd(temp);
			temp = temp->next;
			i++;
			printf("-------------------------------------\n\n");
		}
	}
}

//flags: 1 = local (default) 2 = external 3 = all
void	print_env(t_node *env_list, int flag)
{
	t_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (flag == 1)
		{
			if (temp->type == 1 && check_env_content(temp->content))
				printf("%s\n", temp->content);
		}
		if (flag == 2)
		{
			if (temp->type == 2 && check_env_content(temp->content))
				printf("%s\n", temp->content);
		}
		if (flag == 3)
			if ((temp->type == 1 || temp->type == 2)
				&& check_env_content(temp->content))
				printf("%s\n", temp->content);
		temp = temp->next;
	}
}
