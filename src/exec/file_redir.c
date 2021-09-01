/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:17:14 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/01 08:15:29 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    redir_output(t_shell *s)
{
    if (s->file.ow)
        s->file.fdout = open(s->file.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (s->file.ap)
        s->file.fdout = open(s->file.outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (s->file.fdout < 0)
        bash_error_wFilename(s, s->file.outfile);
    ft_free(s->file.outfile);
}

void    redir_input(t_shell *s)
{
    if (s->file.infile)
        s->file.fdin = open(s->file.infile, O_RDONLY);
    if (s->file.fdin < 0)
        bash_error_wFilename(s, s->file.infile);
    ft_free(s->file.infile);
}

void    redir_heredoc(t_shell *s)
{
    if (s->file.here_doc)
        s->file.fdin = s->file.tmpfd;
    printf("dup %d\n", dup2(s->file.fdin, 0));
	close(s->file.fdin);
    // unlink(TMPFILE);
}
