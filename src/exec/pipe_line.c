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

// static void	last_pipe(t_shell *s)
// {
// 	if (s->file.outfile)
// 		redir_output(s);
// 	else
// 	{
// 		s->file.fdout = dup(s->file.tmpout);
// 		if (!s->file.fdout)
// 			ft_exit(s, "Last pipe");
// 	}
// 	s->file.fdin = s->pipe_one[READ];
// 	close(s->file.fdin);
// }

// static void	parent_waits(t_shell *s)
// {
// 	int	status;

// 	waitpid(g_proc, &status, 0);
// 	close(s->pipe_one[WRITE]);
// 	s->file.fdin = s->pipe_one[READ];
// 	s->cmdretval = WEXITSTATUS(status);
// 	g_proc = 0;
// 	free_arr(s->arg);
// 	reset_shell(s);
// }

// static void	swap_redir(t_shell *s, int i)
// {
// 	if (s->file.stopword)
// 		get_heredoc(s);
// 	if (s->file.infile)
// 		redir_input(s);
// 	dup2(s->file.fdin, READ);
// 	close(s->file.fdin);
// 	if (i == s->pipelen - 1)
// 		last_pipe(s);
// 	else
// 	{
// 		if (s->file.outfile)
// 			redir_output(s);
// 		else
// 		{
// 			s->file.fdout = s->pipe_one[WRITE];
// 			s->file.fdin = s->pipe_one[READ];
// 		}
// 	}
// 	dup2(s->file.fdout, WRITE);
// 	close(s->file.fdout);
// }

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

static int	*switch_pipe(int *other)
{
	int *p;

	p = malloc(sizeof(int) * 2);
	p[0] = other[0];
	p[1] = other[1];
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
		bash_error_cmdNotFound(s, s->arg[0]);
	free_arr(s->arg);
	s->cmdnotfound = 0;
}

static void	switch_pipeFds(int *fd, int new_fd, int REDIR) // subst fd for pipemake
{
	if (REDIR == READ)
	{
		if (*fd == READ)
			*fd = new_fd;
		else
			close(new_fd);
	}
	else if (REDIR == WRITE)
	{
		if (*fd == WRITE)
			*fd = new_fd;
		else
			close(new_fd);
	}

}

static void swapPipes(t_shell *s, int i)
{
	printf("in %d\n", s->file.fdin);
	printf("out %d\n", s->file.fdout);
	if (i > 0)
		switch_pipeFds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->pipelen - 1)
		switch_pipeFds(&s->file.fdout,
			s->pipe_one[WRITE], WRITE);
	else
		close(s->pipe_one[WRITE]);
	printf("in %d\n", s->file.fdin);
	printf("out %d\n", s->file.fdout);
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
		s->arg = parse_arg(s, i);
		g_proc = fork();
		if (g_proc < 0)
		{
			free_arr(s->arg);
			return (perror("Fork"));
		}
		if (!g_proc)
		{
			close(s->pipe_one[READ]);
			reset_shell(s);
			swapPipes(s, i);
			// swap_redir(s, i);
			printf("after %d\n", s->file.fdin);
			printf("after %d\n", s->file.fdout);
			child_process(s);
		}
		else if (g_proc > 0)
			parent_process(s, i);
		// 
	}
	free_arr(s->cmd);
	while (i--)
		wait(&status);
}
