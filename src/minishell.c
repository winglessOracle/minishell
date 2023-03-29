/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/29 21:09:52 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_node		*tokens;
	t_node		*env_list;
	t_pipe		*pipeline;
	char		*line_read;

	atexit(leaks);
	line_read = NULL;
	env_list = env_to_list(envp);
	add_variable(env_list, "PS1=CC_PROMPT:$> ", 1);
	while (1)
	{
		if (line_read)
		{
		  	free(line_read);
		  	line_read = NULL;
		}
		line_read = readline("CC_PROMPT:$> ");
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read)
		 	add_history(line_read);
		tokens = lexer(line_read, "|<> \t\n");
		pipeline = parse_pipeline(tokens, env_list);
	}
	exit(EXIT_SUCCESS);
}
