/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 18:17:40 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/31 17:33:23 by mlazzare         ###   ########.fr       */
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
	if (s->file.infile)
		redir_input(s);
	dup2(s->file.fdin, 0); // protecting this creates troubles, to check
	close(s->file.fdin);
	if (i == s->len - 1)
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
		s->file.fdout = s->pipefd[1];
		s->file.fdin = s->pipefd[0];
	}
	dup2(s->file.fdout, 1); // protecting this creates troubles, to check
	close(s->file.fdout);
}

static void close_fd(t_shell *s)
{
	if (dup2(s->file.tmpin, 0) < 0)
		ft_exit(s);
	if (dup2(s->file.tmpout, 1)  < 0)
		ft_exit(s);
	close(s->file.tmpin);
	close(s->file.tmpout);
	close(s->pipefd[0]);
	close(s->pipefd[1]);
}

void	child_process(t_shell s, char **arg)
{
	int j;
	char *cmd;

	j = -1;
	if (s.file.stopword) // this is for cmd such as 'echo << stopword'
		return (read_heredoc(s, arg));
	// line 89: in case the cmd already comes with absolute path, e.g. /bin/ls
	execve(arg[0], arg, s.e.env); 
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
		arg = parse_arg(&s, i);
		swap_pipe(&s, i);
		reset_shell(&s);
		s.proc = fork();
		if (s.proc < 0)
			return (perror("Fork"));
		if (!s.proc)
			child_process(s, arg);
		// else if (!WIFEXITED(s.status))
		// 	parent_waits(s, s.proc);
	}
	close_fd(&s);
	if (!s.background)
		parent_waits(s, s.proc);
}
