/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:47:45 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/12 13:17:07 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT && g_proc != 0)
	{
		kill(getpid(), SIGCONT);
		write(STDOUT, "\n", 1);
	}
	else if (sig == SIGINT && g_proc == 0)
	{
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT && g_proc != 0)
	{
		if (!kill(g_proc, SIGCONT))
			write(STDOUT, "Quit: 3\n", 8);
	}
	else if (sig == SIGQUIT && g_proc == 0)
		write(STDOUT, "\b \b\b \b", 6);
}

void	handle_sigusr1(int sig)
{
	if (sig == SIGUSR1)
	{
		close(STDIN);
		write(STDOUT, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
}

void	shell_signal()
{
	signal(SIGINT, handle_sigint);
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGQUIT, handle_sigquit);
}