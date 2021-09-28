/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/28 15:43:35 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	*switch_pipe(int *curr_pipe)
{
	int	*p;

	p = malloc(sizeof(int) * 2);
	p[READ] = curr_pipe[READ];
	p[WRITE] = curr_pipe[WRITE];
	return (p);
}

static void	parent_process(t_shell *s, int i)
{
	close(s->pipe_one[WRITE]);
	if (i > 0)
		close(s->pipe_two[READ]);
	if (i == s->pipelen - 1)
		close(s->pipe_one[READ]);
	else
		s->pipe_two = switch_pipe(s->pipe_one);
	close_fds(s);
	free_redir(s);
}

static void	dup_stdinout(t_shell *s)
{
	if (s->file.fdin != READ)
	{
		if (dup2(s->file.fdin, READ) < 0)
			exit(EXIT_FAILURE);
		close(s->file.fdin);
	}
	if (s->file.fdout != WRITE)
	{
		if (dup2(s->file.fdout, WRITE) < 0)
			exit(EXIT_FAILURE);
		close(s->file.fdout);
	}
}

static void	child_process(t_shell *s, int i)
{
	int		j;
	char	*cmd;

	j = -1;
	get_fds(s, i);
	dup_stdinout(s);
	execve(s->arg[0], s->arg, s->minienv);
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], s->arg[0]);
		if (!cmd)
			malloxit();
		execve(cmd, s->arg, s->minienv);
		free(cmd);
	}
}

void	pipe_line(t_shell *s)
{
	int		i;

	i = -1;
	while (s->cmd[++i])
	{
		if (pipe(s->pipe_one) < 0)
			ft_exit(s, "Pipe");
		signal(SIGQUIT, handle_sigquit);
		reset_shell(s);
		s->arg = parse_arg(s, i);
		if (not_pipeable_cmd(s))
			continue ;
		g_proc = fork();
		if (g_proc < 0)
			fork_failed(s);
		if (!g_proc)
			child_process(s, i);
		else if (g_proc > 0)
			parent_process(s, i);
		free_arr(s->arg);
	}
}
