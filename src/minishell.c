/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/24 12:15:39 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	t_node **tokens;
	tokens = malloc(sizeof(t_node **));
	if (!tokens)
		exit_error(21);
	*tokens = NULL;
	char *str = "Hello world>>How| are$YOU|> to||day?";
	lexer(tokens, str, "|&;()<> \t");
			
	//test print
	printf("\nprinting output list of lexer:\n\n");
	printf("tested string:\t\t%s\n", str);
	printf("tested deliminators:\t'|&;()<> '\n");
	
	int i = 1;
	while (*tokens)
	{
		printf("--node [%d]--\ntype\t<%d>\ncontent\t'%s'\n\n", i, (*tokens)->type, (char *)(*tokens)->content);
		*tokens = (*tokens)->next;
		i++;
	}
	
	//test env, move init to init master_struct
	t_node 	**env_list;
	env_list = malloc(sizeof(t_node **));
	if (!env_list)
		exit_error(errno);
	*env_list = NULL;
	env_to_list(envp, env_list);
	print_env(env_list);
	
	exit(EXIT_SUCCESS);
}
