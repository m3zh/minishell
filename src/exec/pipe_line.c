/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/20 15:02:50 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	last_pipe(t_shell *s)
{
	if (s->file.outfile)
		redir_output(s);
	else
	{
		s->file.fdout = dup(s->file.tmpout);
		if (!s->file.fdout)
			ft_exit(s);
	}
	s->file.fdin = s->pipefd[READ];
	close(s->file.fdin);
}

static void	parent_waits(t_shell *s, char **arg)
{
	int	status;

	waitpid(g_proc, &status, 0);
	close(s->pipefd[WRITE]);
	s->file.fdin = s->pipefd[READ];
	s->cmdretval = WEXITSTATUS(status);
	g_proc = 0;
	free_arr(arg);
	reset_shell(s);
}

static void	swap_pipe(t_shell *s, int i)
{
	if (s->file.stopword)
		get_heredoc(s);
	if (s->file.infile)
		redir_input(s);
	dup2(s->file.fdin, READ);
	close(s->file.fdin);
	if (i == s->pipelen - 1)
		last_pipe(s);
	else
	{
		if (s->file.outfile)
			redir_output(s);
		else
		{
			s->file.fdout = s->pipefd[WRITE];
			s->file.fdin = s->pipefd[READ];
		}
	}
	dup2(s->file.fdout, WRITE);
	close(s->file.fdout);
}

static void	child_process(t_shell *s, char **arg, int i)
{
	int		j;
	char	*cmd;

	j = -1;
	(void)i;
	execve(arg[0], arg, s->minienv);
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], arg[0]);
		if (!cmd)
			malloxit();
		execve(cmd, arg, s->minienv);
		free(cmd);
		s->cmdnotfound = 1;
	}
	if (s->cmdnotfound)
		bash_error_cmdNotFound(s, arg[0]);
	free_arr(arg);
	s->cmdnotfound = 0;
}

void	pipe_line(t_shell *s)
{
	int		i;
	char	**arg;

	i = -1;
	while (s->cmd[++i] && !s->error_skip)
	{
		if (pipe(s->pipefd) < 0)
			ft_exit(s);
		signal(SIGQUIT, handle_sigquit);
		arg = parse_arg(s, i);
		swap_pipe(s, i);
		reset_shell(s);
		g_proc = fork();
		if (g_proc < 0)
		{
			free_arr(arg);
			return (perror("Fork"));
		}
		if (!g_proc)
			child_process(s, arg, i);
		else if (g_proc > 0)
			parent_waits(s, arg);
	}
	free_arr(s->cmd);
}
