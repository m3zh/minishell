/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:47:26 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/26 14:24:46 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	close_pipe(t_shell *s, int i)
{
	int	status;

	if (s->pipe_two)
		free(s->pipe_two);
	free_arr(s->cmd);
	while (i--)
		wait(&status);
}

static void	exec_builtins(t_shell *shell)
{
	stop(shell);
	cd(shell);
	enver(shell);
}

void	exec_shell(t_shell *s)
{
	int	i;

	if (s->pipelen <= 1)
	{
		signal(SIGQUIT, handle_sigquit);
		exec_builtins(s);
	}
	if (s->builtin)
		return (free_arr(s->cmd));
	i = pipe_line(s);
	close_pipe(s, i);
}
