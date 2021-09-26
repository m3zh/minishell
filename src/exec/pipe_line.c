/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/24 07:19:01 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	swap_redir(t_shell *s)
{
	close(s->pipe_one[READ]);
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.infile)
		redir_input(s);
	if (s->file.outfile)
		redir_output(s);
}

static void	close_fds(t_shell *s)
{
	if (s->file.fdin != READ)
	{
		close(s->file.fdin);
		s->file.fdin = READ;
	}
	if (s->file.fdout != WRITE)
	{
		close(s->file.fdout);
		s->file.fdout = WRITE;
	}
}

static int	*switch_pipe(int *curr_pipe)
{
	int *p;

	p = malloc(sizeof(int) * 2);
	p[0] = curr_pipe[0];
	p[1] = curr_pipe[1];
	return (p);
}

static void parent_process(t_shell *s, int i)
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

static void closeStdInOut(t_shell *s)
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

static void	child_process(t_shell *s)
{
	int		j;
	char	*cmd;

	j = -1;
	closeStdInOut(s);
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

void	pipe_line(t_shell *s)
{
	int		status;
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
		{
			swap_redir(s);
			swap_pipe(s, i);
			child_process(s);
		}
		else if (g_proc > 0)
			parent_process(s, i);
	}
	free_arr(s->cmd);
	while (i--)
		wait(&status);
}
