/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/04 11:29:42 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp) //remove arguments and return type?
{
	t_node		*tokens;
	t_node		*env_list;
	char		*line_read;
	char		*prompt;

	(void)argc;
	(void)argv;
	atexit(leaks);
	line_read = NULL;
	env_list = env_to_list(envp);
	init_variables(env_list);
	set_sig_term();
	read_history("log/history_log"); //remove?
	while (1)
	{
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
		prompt = get_variable(env_list, "PS1");
		line_read = readline(prompt);
		if (!ft_strcmp(line_read, "exit") || line_read == NULL)
			break ;
		if (line_read && *line_read)
			add_history(line_read);
	//	run_tests(line_read, tokens, env_list);
		if (tokens)
			lstclear(&tokens, delete_content);
		free(prompt);
	}
	write_history("log/history_log"); //remove?
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
