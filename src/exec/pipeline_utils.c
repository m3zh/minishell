/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:30:47 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/28 14:33:21 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	invalid_cmd(t_shell *s)
{
	if (is_builtin(s->arg[0]) || not_executable(s, s->arg[0]))
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

static void	switch_pipefds(int *fd, int new_fd, int REDIR)
{
	if (*fd == REDIR)
		*fd = new_fd;
	else
		close(new_fd);
}

void	get_fds(t_shell *s, int i)
{
	close(s->pipe_one[READ]);
	checkfile_redir(s);
	if (i > 0)
		switch_pipefds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->pipelen - 1)
		switch_pipefds(&s->file.fdout,
			s->pipe_one[WRITE], WRITE);
	else
		close(s->pipe_one[WRITE]);
}
