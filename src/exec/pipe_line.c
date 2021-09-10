/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/10 15:37:00 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parent_waits(t_shell *s)
{
	int status;

	waitpid(g_proc, &status, WUNTRACED | WCONTINUED);
	s->cmdretval = WEXITSTATUS(status);
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

static void	child_process(t_shell *s, char **arg)
{
	int j;
	char *cmd;

	j = -1;
	execve(arg[0], arg, s->e.env); // line 89: in case the cmd already comes with absolute path, e.g. /bin/ls
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], arg[0]);
		if (!cmd)
			return ;
		execve(cmd, arg, s->e.env);
		free(cmd);
		s->cmdnotfound = 1;
	}
	if (s->cmdnotfound)
		bash_error_cmdNotFound(s, arg[0]);
	free_arr(arg);
	s->cmdnotfound = 0;
}

void    pipe_line(t_shell *s)
{
	int		i;
    char	**arg;

    i = -1;
	while (s->cmd[++i])
	{
		arg = parse_arg(s, i);
		swap_pipe(s, i);
		reset_shell(s);
		g_proc = fork();
		if (g_proc < 0)
			return (perror("Fork"));
		if (!g_proc)
			child_process(s, arg);
		else if (g_proc > 0)
			parent_waits(s);
	}
}
