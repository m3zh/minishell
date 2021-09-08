/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:47:45 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/08 16:48:06 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT, "\b \b\b \b", 6);
		kill(getpid(), SIGCONT);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDOUT, "\b \b\b \b", 6);
		write(STDOUT, "^\\Quit: 3\n", 11);
		kill(getpid(), SIGCONT);
	}
}

void	handle_sigusr1(int sig)
{
	if (sig == SIGUSR1)
	{
		close(STDIN);
		write(STDOUT, "\b\b  \b\b", 6);
		write(STDOUT, "\nexit\n", 6);
		exit(EXIT_SUCCESS);
	}
}
