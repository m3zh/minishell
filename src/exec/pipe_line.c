/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/24 06:20:46 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	last_pipe(t_shell *s, int i)
{
	while (i + 1000000 > 0)
		i--;
	if (s->file.outfile)
		redir_output(s);
	else
	{
		s->file.fdout = dup(s->file.tmpout);
		if (!s->file.fdout)
			ft_exit(s);
	}
}

static void	close_fd(t_shell *s, int i, int (*pipefd)[2])
{
	if (dup2(s->file.tmpin, READ) < 0)
		ft_exit(s);
	if (dup2(s->file.tmpout, WRITE) < 0)
		ft_exit(s);
	close(s->file.tmpin);
	close(s->file.tmpout);
	while (i-- >= 0)
	{
		close(pipefd[i][READ]);
		close(pipefd[i][WRITE]);
	}
}

static void	swap_pipe(t_shell *s, int i, int (*pipefd)[2])
{
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.infile)
		redir_input(s);
	else if (i > 0)
		s->file.fdin = pipefd[i - 1][READ];
	dup2(s->file.fdin, READ);
	close(s->file.fdin);
	if (i == s->pipelen - 1)
		last_pipe(s, i);
	else
	{
		if (s->file.outfile)
			redir_output(s);
		else
		{
			s->file.fdout = pipefd[i][WRITE];
			if (i > 0)
				s->file.fdin = pipefd[i - 1][READ];
		}
	}
	if (dup2(s->file.fdout, WRITE) < 0)
		exit(EXIT_FAILURE);
	close(s->file.fdout);
}

static void	child_process(t_shell *s)
{
	int		j;
	char	*cmd;

	j = -1;
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
	int		status;
	int		pipefd[s->pipelen][2];

	i = -1;
	while (s->cmd[++i] && !s->error_skip)
	{
		if (pipe(pipefd[i]) < 0)
			ft_exit(s);
		signal(SIGQUIT, handle_sigquit);
		s->arg = parse_arg(s, i);
		if (is_builtin(s->arg[0]) || not_executable(*s, s->arg[0]))
		{
			free_arr(s->arg);
			continue ;
		}
		g_proc = fork();
		swap_pipe(s, i, pipefd);
		reset_shell(s);
		if (g_proc < 0)
		{
			free_arr(s->arg);
			perror("Fork");
			exit(EXIT_FAILURE);
		}
		if (!g_proc)
			child_process(s);
		if (!s->cmdnotfound)
			free(s->arg);
		else
			waitpid(g_proc, &status, WUNTRACED | WNOHANG);
	}
	free_arr(s->cmd);
	close_fd(s, i, pipefd);
	while (i--)
		wait(NULL);
	g_proc = 0;
}
