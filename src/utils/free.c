/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:36:31 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/30 21:12:15 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free(char *s)
{
	if (s)
		free(s);
	s = NULL;
}

int	free_arr(char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
		free(path[i++]);
	if (path)
		free(path);
	return (0);
}

void	free_struct(t_shell *s)
{
	free_arr(s->cmd);
	free_arr(s->path);
	free_arr(s->args);
}

int	ft_exit(t_shell *shell)
{
	free_struct(shell);
	exit(EXIT_FAILURE);
}