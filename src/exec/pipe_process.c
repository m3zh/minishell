/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 18:17:40 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/16 15:27:41 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parent_waits(t_shell s, pid_t proc)
{
	if (waitpid(proc, &s.status, 0) < 1)
	{
			perror("Waitpid");
			ft_exit(&s);
	}
}
static void open_fd(t_shell *s)
{
	s->tmpin = dup(0);
	s->tmpout = dup(1);
	if (s->infile)
		s->fdin = open(s->infile, O_RDONLY);
	else
		s->fdin = dup(s->tmpin);
	s->fdout = dup(s->tmpout);
}

static void swap_pipe(t_shell *s, int i)
{
	dup2(s->fdin, 0);
	close(s->fdin);
	if (i == s->len - 1)
	{
		if (s->outfile)
			redir_output(s);
		else
			s->fdout = dup(s->tmpout);
	}		
	else
	{
		s->fdout = s->pipefd[1];
		s->fdin = s->pipefd[0];
	}
	dup2(s->fdout, 1);
	close(s->fdout);
}

static void close_fd(t_shell *s)
{
	dup2(s->tmpin, 0);
	dup2(s->tmpout, 1);
	close(s->tmpin);
	close(s->tmpout);
	close(s->pipefd[0]);
	close(s->pipefd[1]);
}

static void	child_process(t_shell s, char **arg)
{
	int j;
	char *cmd;

	j = -1;
	while (s.path[++j])
	{
		cmd = ft_join(s.path[j], arg[0]);
		if (!cmd)
			return ;
		execve(cmd, arg, s.e.env);
		free(cmd);
	}
	bash_error_wFilename(&s, arg[0]);
	exit(EXIT_FAILURE);
}

void	bash_cmd(t_shell s)
{
	int		i;
	char	**arg;

	i = -1;
	open_fd(&s);
	pipe(s.pipefd);
	while (s.cmd[++i])
	{
		// if (!s.proc)
		// 	waitpid(s.proc, &s.status, 0);
		arg = parse_arg(&s, i);
		swap_pipe(&s, i);
		reset_shell(&s);
		s.proc = fork();
		if (s.proc < 0)
			return (perror("Fork"));
		if (!s.proc)
			child_process(s, arg);
	}
	close_fd(&s);
	if (!s.background)
		parent_waits(s, s.proc);
}
