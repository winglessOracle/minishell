/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 12:30:55 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/12 11:42:38 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sigterm.h"

void	exit_sig(t_node *env_list)
{
	char	*str;

	str = get_variable(env_list, "PS1");
	if (!str)
		exit_error("exit_sig", 1);
	printf("%s exit\n", str);
	free(str);
	exit(g_exit_status);
}

void	reset_terminal(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &t);
}

void	handle_sigint_here(int signal_number)
{
	(void) signal_number;
	signal(SIGINT, SIG_DFL);
	kill(0, SIGINT);
	exit(1);
}

void	handle_sigint(int signal_number)
{
	pid_t	pid;
	int		status;

	(void) signal_number;
	pid = waitpid(-1, &status, WNOHANG);
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	if (pid == -1)
		rl_redisplay();
}

// rl_catch_signals = 0;
void	set_signals(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_stop;
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
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

void	set_sigint_here(void)
{
	struct sigaction	sa_here;

	sa_here.sa_handler = handle_sigint_here;
	sa_here.sa_flags = 0;
	sigemptyset(&sa_here.sa_mask);
	sigaddset(&sa_here.sa_mask, SIGINT);
	sigaddset(&sa_here.sa_mask, SIGQUIT);
	sigaddset(&sa_here.sa_mask, SIGTSTP);
	if (sigaction(SIGINT, &sa_here, NULL) == -1)
		exit(errno);
}
