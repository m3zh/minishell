/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:24:04 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/16 15:02:06 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    reset_string(char **s, int i)
{
    if (s && s[i])
    {
        free(s[i]);
        s[i] = NULL;
    }
}

void    reset_shell(t_shell *s)
{
	s->infile = 0;
	s->outfile = 0;
	s->errfile = 0;
    s->ap = 0;
    s->ow = 0;
}