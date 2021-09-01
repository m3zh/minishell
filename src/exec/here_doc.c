/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/01 08:13:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void swap_pipe_wHeredoc(t_shell *s, int i)
{
	if (s->file.stopword)
		redir_heredoc(s);
	if (i == s->len - 1)
	{
		if (s->file.outfile)
			redir_output(s);
		else
		{
			s->file.fdout = dup(s->file.tmpout);
			if (!s->file.fdout)
				ft_exit(s);
		}
	}		
	else
	{
		s->file.fdout = s->pipefd[1];
		s->file.fdin = s->pipefd[0];
	}
	dup2(s->file.fdout, 1); // protecting this breaks up the pipe, to check
	close(s->file.fdout);
}

void    read_heredoc(t_shell *s, char **arg, int i)
{
    int     j;
    char	*word;

    (void)i;
    word = 0;
    j = 0;
    while (arg[j])
        j++;
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
    // arg[j] = ft_strdup(TMPFILE);
    // arg[j + 1] = 0;
    swap_pipe_wHeredoc(s, i);
    s->file.more = 0;
    s->file.stopword = 0;
}