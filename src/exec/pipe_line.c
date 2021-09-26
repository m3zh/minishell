/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/26 14:30:51 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	*switch_pipe(int *curr_pipe)
{
	int	*p;

	p = malloc(sizeof(int) * 2);
	p[0] = curr_pipe[0];
	p[1] = curr_pipe[1];
	return (p);
}

static void	parent_process(t_shell *s, int i)
{
	close(s->pipe_one[WRITE]);
	if (i > 0)
		close(s->pipe_two[0]);
	if (i == s->pipelen - 1)
		close(s->pipe_one[READ]);
	else
		s->pipe_two = switch_pipe(s->pipe_one);
	close_fds(s);
}

static void	closestdinout(t_shell *s)
{
	if (s->file.fdin != READ)
	{
		if (dup2(s->file.fdin, READ) < 0)
			ft_exit(s, "Close stdin");
		close(s->file.fdin);
	}
	if (s->file.fdout != WRITE)
	{
		if (dup2(s->file.fdout, WRITE) < 0)
			ft_exit(s, "Close stdout");
		close(s->file.fdout);
	}
}

static void	child_process(t_shell *s, int i)
{
	int		j;
	char	*cmd;

	j = -1;
	get_fds(s, i);
	if (s->error_skip)
		return ;
	closestdinout(s);
	execve(s->arg[0], s->arg, s->minienv);
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], s->arg[0]);
		if (!cmd)
			malloxit();
		execve(cmd, s->arg, s->minienv);
		free(cmd);
		s->cmdnotfound = 1;
	}
	if (s->cmdnotfound)
		bash_error_cmd_not_found(s, s->arg[0]);
	free_arr(s->arg);
	s->cmdnotfound = 0;
}

int	pipe_line(t_shell *s)
{
	int		i;

	i = -1;
	while (s->cmd[++i] && !s->error_skip)
	{
		if (pipe(s->pipe_one) < 0)
			ft_exit(s, "Pipe");
		signal(SIGQUIT, handle_sigquit);
		reset_shell(s);
		s->arg = parse_arg(s, i);
		g_proc = fork();
		if (g_proc < 0)
			fork_failed(s);
		if (!g_proc)
			child_process(s, i);
		else if (g_proc > 0)
			parent_process(s, i);
	}
	return (i);
}
