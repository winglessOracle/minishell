/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/18 09:43:22 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	exit_sig(t_node *env_list)
{
	char	*str;

	str = get_variable(env_list, "PS1");
	if (!str)
		exit_error("exit_sig", 1);
	printf("%s exit\n", str);
	free(str);
	// if (g_exit_status)  // dit is niet meer nodig denk ik?
	// 	g_exit_status = 1;
	exit(g_exit_status);
}

void	handle_sigint_here(int signal_number)
{
	(void) signal_number;
	_exit(131);  //child exit
	// signal(SIGINT, SIG_DFL);
	// kill(getpid(), SIGINT);  // moet dit zo? (afgekeken van sigquit)
}

// void	handle_sigquit(int signal_number) // aangepast naar sig_dfl in executor
// {
// 	(void) signal_number;
// 	// printf("Quit (core dumped)\n");
// 	// kill(getpid(), SIGQUIT);
// 	// g_exit_status = 131; //remove? ja kan er uit volgens mij :)
// }

void	handle_sigint(int signal_number)
{
	pid_t	pid;
	int		status;

	(void) signal_number;
	pid = waitpid(-1, &status, WNOHANG);
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	// g_exit_status = 130; //remove?  ja kan er uit volgens mij :)
	if (pid == -1)
		rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
