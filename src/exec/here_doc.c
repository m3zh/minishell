/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/31 21:25:34 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    read_heredoc(t_shell *s, char **arg)
{
    int     tmpfd;
    char	*word;

    (void)arg;
    word = 0;
    tmpfd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tmpfd < 0)
        ft_exit(s);
    while (1)
    {
		word = readline("> ");
        if (!ft_strcmp(word, s->file.stopword))
            break ;
        if (!s->file.more)
            write(tmpfd, word, ft_strlen(word)); // add \n
    }
    redir_heredoc(s, tmpfd);
    s->file.more = 0;
    s->file.stopword = 0;
}