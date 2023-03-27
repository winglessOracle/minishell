/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/27 15:19:35 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc; //waarom is dit?
	(void)argv;
	t_node **tokens;
	t_master *master;

	atexit(leaks);
	char *str = "'Hello' world>>How| are$YOU|> to||day?";
	master = init_master_struct();
	master->env_list = env_to_list(envp);
	tokens = lexer(str, "|<> \t\n"); //&;() ignored for now
	// master->commands =

	//tests
	// run_tests(str, tokens, master);
	lstclear(tokens, delete_content);
	
	exit(EXIT_SUCCESS);
}
