/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/01 08:47:50 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    get_heredoc(t_shell *s)
{
    char	*word;

    word = 0;
    s->file.tmpfd = open(TMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (s->file.tmpfd < 0)
        ft_exit(s);
    while (1)
    {
		word = readline("> ");
        if (!ft_strcmp(word, s->file.stopword))
            break ;
        if (!s->file.more)
        {
            write(s->file.tmpfd, word, ft_strlen(word));
            write(s->file.tmpfd, "\n", 1);
        }
    }
    redir_heredoc(s);
    s->file.more = 0;
    s->file.stopword = 0;
}
