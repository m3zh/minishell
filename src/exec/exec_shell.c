/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:47:26 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/24 07:20:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	open_fd(t_shell *s)
{
	(void)s;
	// s->file.tmpin = dup(0);
	// if (s->file.tmpin < 0)
	// 	ft_exit(s, "Tmpin dup");
	// s->file.tmpout = dup(1);
	// if (s->file.tmpout < 0)
	// 	ft_exit(s, "Tmpout dup");
	// s->file.fdin = dup(0);
	// if (s->file.fdin < 0)
	// 	ft_exit(s, "Fdin dup");
	// s->file.fdout = dup(1);
	// if (s->file.fdout < 0)
	// 	ft_exit(s, "Fdout dup");
}

static void	close_fd(t_shell *s)
{
	(void)s;
	// if (dup2(s->file.tmpin, READ) < 0)
	// 	ft_exit(s, "Tmpin close");
	// if (dup2(s->file.tmpout, WRITE) < 0)
	// 	ft_exit(s, "Tmpout close");
	// close(s->file.tmpin);
	// close(s->file.tmpout);
	// close(s->pipe_one[READ]);
	// close(s->pipe_one[WRITE]);
}

static void	exec_builtins(t_shell *shell)
{
	stop(shell);
	cd(shell);
	enver(shell);
}

void	exec_shell(t_shell *s)
{
	// int	status;

	if (s->pipelen <= 1)
	{
		signal(SIGQUIT, handle_sigquit);
		exec_builtins(s);
	}
	if (s->builtin)
		return (free_arr(s->cmd));
	open_fd(s);
	pipe_line(s);
	close_fd(s);
	// waitpid(g_proc, &status, 0);
}
