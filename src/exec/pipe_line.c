/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/07 18:48:24 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parent_waits(t_shell s, pid_t proc)
{
	int status;

	(void)s;
	waitpid(proc, &status, 0);
}
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

static void swap_pipe(t_shell *s, int i)
{
	if (s->file.stopword) // this is for cmd such as 'echo << stopword'
		get_heredoc(s);
	if (s->file.infile)
		redir_input(s);
	dup2(s->file.fdin, READ); // protecting this breaks up the pipe, to check
	close(s->file.fdin);
	if (i == s->pipelen - 1)
	{
		if (s->file.outfile)
			redir_output(s);
		else
		{
			s->file.fdout = dup(s->file.tmpout);
			if (!s->file.fdout)
				ft_exit(s);
		}
	}		
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
	dup2(s->file.fdout, WRITE); // protecting this breaks up the pipe, to check
	close(s->file.fdout);
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

static void	child_process(t_shell s, char **arg, int i)
{
	int j;
	char *cmd;

	j = -1;
	(void)i;
	// line 89: in case the cmd already comes with absolute path, e.g. /bin/ls
	execve(arg[READ], arg, s.e.env); 
	while (s.path[++j])
	{
		cmd = ft_join(s.path[j], arg[READ]);
		if (!cmd)
			return ;
		execve(cmd, arg, s.e.env);
		free(cmd);
	}
	bash_error_wFilename(&s, arg[READ]);
	exit(EXIT_FAILURE);
}

void	exec_shell(t_shell s)
{
	int		i;
	int		status;
	char	**arg;

	i = -1;
	open_fd(&s);
	if (pipe(s.pipefd) < 0)
		ft_exit(&s);
	while (s.cmd[++i])
	{
		arg = parse_arg(&s, i);
		swap_pipe(&s, i);
		reset_shell(&s);
		s.proc = fork();
		if (s.proc < 0)
			return (perror("Fork"));
		if (!s.proc)
			child_process(s, arg, i);
		else if (s.proc < 0 && !WIFEXITED(status))
			parent_waits(s, s.proc);
	}
	close_fd(&s);
	if (!s.background)
		parent_waits(s, s.proc);
	free_struct(&s);
}
