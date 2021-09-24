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

void	wait_pid(int i)
{
	while (i + WAIT > 0)
		i--;
}
