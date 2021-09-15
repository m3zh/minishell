/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:47:26 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/15 11:28:05 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void open_fd(t_shell *s)
{
	s->file.tmpin = dup(0);
	if (s->file.tmpin < 0)
		ft_exit(s);
	s->file.tmpout = dup(1);
	if (s->file.tmpout < 0)
		ft_exit(s);
	if (s->file.infile)
		redir_input(s);
	else
	{
		s->file.fdin = dup(s->file.tmpin);
		if (s->file.fdin < 0)
			ft_exit(s);
	}
	s->file.fdout = dup(s->file.tmpout);
	if (s->file.fdout < 0)
		ft_exit(s);
}

static void close_fd(t_shell *s)
{
	if (dup2(s->file.tmpin, READ) < 0)
		ft_exit(s);
	if (dup2(s->file.tmpout, WRITE)  < 0)
		ft_exit(s);
	close(s->file.tmpin);
	close(s->file.tmpout);
	close(s->pipefd[READ]);
	close(s->pipefd[WRITE]);
}

static void exec_builtins(t_shell *shell)
{
    stop(shell);
    cd(shell);
    enver(shell);
}

void	exec_shell(t_shell *s)
{
    int status;
    
    if (s->pipelen <= 1)
	{
		signal(SIGQUIT, handle_sigquit);
		exec_builtins(s);
	}
	if (s->builtin)
		return (free_arr(s->cmd));        
	open_fd(s);
	if (pipe(s->pipefd) < 0)
		ft_exit(s);
	signal(SIGQUIT, handle_sigquit);
    pipe_line(s);
	close_fd(s);
    waitpid(g_proc, &status, 0);
	reset_shell(s);
}
