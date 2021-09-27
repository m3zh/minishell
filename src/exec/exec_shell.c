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

static void	get_cmd_retvalue(t_shell *s, int status)
{
	if (WIFEXITED(status))
		s->cmdretval = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->cmdretval = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		s->cmdretval = WSTOPSIG(status);
}

static void	close_pipe(t_shell *s)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	if (s->pipe_two && s->pipelen > 0)
		free(s->pipe_two);
	free_arr(s->cmd);
	while (++i < s->pipelen)
	{
		pid = wait(&status);
		if (pid == g_proc)
			get_cmd_retvalue(s, status);
	}
	g_proc = 0;
}

static void	exec_builtins(t_shell *shell)
{
	signal(SIGQUIT, handle_sigquit);
	stop(shell);
	cd(shell);
	enver(shell);
}

void	exec_shell(t_shell *s)
{
	if (s->pipelen <= 1)
		exec_builtins(s);
	if (s->builtin)
		return (free_arr(s->cmd));
	pipe_line(s);
	close_pipe(s);
}
