/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/24 07:20:26 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	invalid_cmd(t_shell *s)
{
	if (is_builtin(s->arg[0]) || not_executable(*s, s->arg[0]))
	{
		free_arr(s->arg);
		return (1);
	}
	return (0);
}

void	fork_failed(t_shell *s)
{
	if (s->pipe_two)
		free(s->pipe_two);
	free_arr(s->arg);
	perror("Fork");
	exit(EXIT_FAILURE);
}

void	close_fds(t_shell *s)
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

static void	switch_pipeFds(int *fd, int new_fd, int REDIR)
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

void	get_fds(t_shell *s, int i)
{
	close(s->pipe_one[READ]);
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.infile)
		redir_input(s);
	if (s->file.outfile)
		redir_output(s);
	if (s->error_skip)
		return ;
	if (i > 0)
		switch_pipeFds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->pipelen - 1)
		switch_pipeFds(&s->file.fdout,
			s->pipe_one[WRITE], WRITE);
	else
		close(s->pipe_one[WRITE]);
}
