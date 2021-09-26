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
	free_arr(s->arg);
	perror("Fork");
	exit(EXIT_FAILURE);
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

void swap_pipe(t_shell *s, int i)
{
	if (i > 0)
		switch_pipeFds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->pipelen - 1)
		switch_pipeFds(&s->file.fdout,
			s->pipe_one[WRITE], WRITE);
	else
		close(s->pipe_one[WRITE]);
}
