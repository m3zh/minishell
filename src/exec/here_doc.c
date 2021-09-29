/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/29 18:09:39 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	redir_heredoc(t_shell *s)
{
	close(s->file.tmpfd);
	if (s->file.here_doc)
		s->file.fdin = open(TMPFILE, O_RDWR);
	if (s->file.fdin < 0)
		bash_error_w_filename(s, s->file.infile);
	unlink(TMPFILE);
}

int		heredoc_with_nocmd(t_shell *s)
{
	char	*word;

	if (!s->file.stopword || (s->file.stopword && s->arg[0]))
		return (0);
	while (1)
	{
		word = readline("> ");
		if (!ft_strcmp(word, s->file.stopword))
			break ;
		free(word);
	}
	free(word);
	free(s->file.stopword);
	s->file.stopword = 0;
	checkfile_redir(s);
	return (1);
		
}

void	get_heredoc(t_shell *s)
{
	char	*word;

	shell_signal();
	word = 0;
	s->file.tmpfd = open(TMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (s->file.tmpfd < 0)
		perror("");
	while (1)
	{
		word = readline("> ");
		if (!ft_strcmp(word, s->file.stopword))
			break ;
		write(s->file.tmpfd, word, ft_strlen(word));
		write(s->file.tmpfd, "\n", 1);
		ft_free(word);
	}
	ft_free(word);
	if (not_executable_cmd(s, s->arg[0]))
	{
		ft_free(s->file.stopword);
		s->error_skip = 1;
		return ;
	}
	redir_heredoc(s);
	ft_free(s->file.stopword);
}
