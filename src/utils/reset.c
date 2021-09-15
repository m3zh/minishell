/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:24:04 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/15 13:15:46 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_string(char **s, int i)
{
	if (s && s[i])
	{
		free(s[i]);
		s[i] = NULL;
	}
}

void	reset_shell(t_shell *s)
{
	ft_free(s->file.infile);
	ft_free(s->file.outfile);
	ft_free(s->file.errfile);
	ft_free(s->file.stopword);
	s->file.ow = 0;
	s->file.ap = 0;
	s->file.input = 0;
	s->file.here_doc = 0;
}
