/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/30 15:43:37 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");	
}

int	main(void)
{
	t_node		*tokens;
	t_node		*env_list;
	t_pipe		*pipeline;
	char		*line_read;

	// atexit(leaks);
	line_read = NULL;
	env_list = init_env();
	while (1)
	{
		line_read = readline("CC_PROMPT:$> "); // line is freed in lexer after processing
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read)
		 	add_history(line_read);
	printf("READ INPUT\n");
		tokens = lexer(line_read, "|<> \t\n");
	printf("MERGED TOKENS\n");
	print_tokens(tokens);
		pipeline = parse_pipeline(tokens, env_list);
	printf("CREATED PIPLINE\n");
	print_pipeline(pipeline);
	}
	exit(EXIT_SUCCESS);
}
