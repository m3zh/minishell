/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:24:04 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/26 14:37:10 by gneve            ###   ########.fr       */
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
	s->error_skip = 0;
	s->cmdnotfound = 0;
	s->file.infile = 0;
	s->file.outfile = 0;
	s->file.stopword = 0;
	s->file.ow = 0;
	s->file.ap = 0;
	s->file.input = 0;
	s->file.here_doc = 0;
}
