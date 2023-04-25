/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/25 20:06:39 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "sigterm.h"

void	set_sig_term(void)
{
	//set_termios();
	set_signals();
}

void	exit_sig(t_node *env_list)
{
	char	*str;

	str = get_variable(env_list, "PS1");
	if (!str)
		exit_error("exit_sig", 1);
	printf("%s exit\n", str);
	free(str);
	lstclear(&env_list, delete_content);
	exit(g_exit_status);
}

void	handle_sigint(int signal_number)
{
	(void) signal_number;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_stop;
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	// sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sigaddset(&sa_int.sa_mask, SIGTSTP);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		exit(errno);

	sa_stop.sa_handler = SIG_IGN;
	sigemptyset(&sa_stop.sa_mask);
	sigaddset(&sa_stop.sa_mask, SIGINT);
	sigaddset(&sa_stop.sa_mask, SIGQUIT);
	sigaddset(&sa_stop.sa_mask, SIGTSTP);
	if (sigaction(SIGTSTP, &sa_stop, NULL) == -1)
		exit(errno);

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaddset(&sa_quit.sa_mask, SIGTSTP);
	if (sigaction(SIGQUIT, &sa_stop, NULL) == -1)
		exit(errno);
}
