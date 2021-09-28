/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/28 15:24:51 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	redir_heredoc(t_shell *s)
{
	close(s->file.tmpfd);
	if (s->file.here_doc)
		s->file.fdin = open(TMPFILE, O_RDONLY);
	if (s->file.fdin < 0)
		bash_error_w_filename(s, s->file.infile);
	unlink(TMPFILE);
}

void	get_heredoc(t_shell *s)
{
	char	*word;

	word = 0;
	// if (s->file.ow)
	// 	s->file.tmpfd = open(s->file.outfile,
	// 			O_CREAT | O_RDWR | O_TRUNC, 0644);
	// else if (s->file.ap)
	// 	s->file.tmpfd = open(s->file.outfile,
	// 			O_CREAT | O_RDWR | O_APPEND, 0644);
	// else
	s->file.tmpfd = open(TMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (s->file.tmpfd < 0)
		ft_exit(s, "Heredoc");
	while (1)
	{
		word = readline("> ");
		if (!ft_strcmp(word, s->file.stopword))
			break ;
		write(s->file.tmpfd, word, ft_strlen(word));
		write(s->file.tmpfd, "\n", 1);
		free(word);
	}
	redir_heredoc(s);
	ft_free(word);
	ft_free(s->file.stopword);
	s->file.more = 0;
	// if (s->file.ow)
	// 	s->file.ow = 0;
	// else if (s->file.ap)
	// 	s->file.ap = 0;
}
