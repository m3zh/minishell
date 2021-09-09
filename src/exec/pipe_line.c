/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/09 14:55:24 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parent_waits(t_shell *s)
{
	int status;

	(void)s;
	waitpid(g_proc, &status, 0);
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
	(void)i;
	// line 89: in case the cmd already comes with absolute path, e.g. /bin/ls
	execve(arg[READ], arg, s->e.env); 
	while (s->path[++j])
	{
		cmd = ft_join(s->path[j], arg[READ]);
		if (!cmd)
			return ;
		execve(cmd, arg, s->e.env);
		free(cmd);
	}
	// to add msg command not found
	bash_error_wFilename(s, arg[READ]);
	// exit(EXIT_FAILURE);
}

void    pipe_line(t_shell *s)
{
	int		i;
	int		status;
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
			child_process(s, arg, i);
		else if (g_proc < 0 && !WIFEXITED(status))
			parent_waits(s);
	}
}
