/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:17:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/16 14:39:11 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    redir_output(t_shell *s)
{
    if (s->ow)
        s->fdout = open(s->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (s->ap)
        s->fdout = open(s->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (s->fdout < 0)
        bash_error_wFilename(s, s->outfile);
}
