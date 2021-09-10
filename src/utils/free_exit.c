/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:36:31 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/10 19:22:09 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	malloxit(void)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR);
	exit(EXIT_FAILURE);
}

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
	free_arr(s->e.env);
	if (s->path)
		free(s->path);
	if (s->file.stopword)
		free(s->file.stopword);
	if (s->file.infile)
		free(s->file.infile);
	if (s->file.outfile)
		free(s->file.outfile);
	if (s->file.errfile)
		free(s->file.errfile);
	rl_clear_history();
}

int	ft_exit(t_shell *shell)
{
	free_struct(shell);
	exit(EXIT_SUCCESS);
}
