/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/23 20:56:44 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	last_pipe(t_shell *s, int i)
{
	// (void)i;
	// int status;
	
	// waitpid(g_proc, &status, WUNTRACED | __W_CONTINUED);	
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
	int		pipefd[s->pipelen][2];
	int		i;
	int		status;
	char	**arg;

	i = -1;
	while (s->cmd[++i])
	{
		if (pipe(pipefd[i]) < 0)
			ft_exit(s);
		signal(SIGQUIT, handle_sigquit);
		arg = parse_arg(s, i);
		g_proc = fork();
		swap_pipe(s, i, pipefd);
		reset_shell(s);
		if (g_proc < 0)
		{
			free_arr(arg);
			return (perror("Fork"));
		}
		if (!g_proc)
			child_process(s, arg, i);
		waitpid(g_proc, &status, WUNTRACED | WNOHANG);
	}
	free_arr(s->cmd);
	close_fd(s, i, pipefd);
	while(i--)
		wait(NULL);
	g_proc = 0;
}
