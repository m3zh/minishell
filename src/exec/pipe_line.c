/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/14 19:53:10 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parent_waits(t_shell *s, char **arg)
{
	int status;

	waitpid(g_proc, &status, WUNTRACED | WCONTINUED);
	s->cmdretval = WEXITSTATUS(status);
	g_proc = 0;
	free_arr(arg);
	// reset_shell(s);
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

static void	child_process(t_shell *s, char **arg, int i)
{
	int j;
	char *cmd;

	j = -1;
	swap_pipe(s, i);
	// reset_shell(s);
	execve(arg[0], arg, s->minienv); // line 89: in case the cmd already comes with absolute path, e.g. /bin/ls
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], arg[0]);
		if (!cmd)
			malloxit() ;
		execve(cmd, arg, s->minienv);
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
