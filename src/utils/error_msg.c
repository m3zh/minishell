/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:59:31 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/21 08:59:33 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
 * unexpectedToken error displays when redirections (<,<<,>>,>)
 * are not followed by a valid file, e.g. echo hello > | cat myfile;
 * or when pipe is misplaced
 */

void	bash_error_unexpectedToken(t_shell *s, int err)
{
	if (!err)
		write(STDERR_FILENO,
			"-bash: syntax error near unexpected token `newline'\n", 52);
	else if (err == 2)
		write(STDERR_FILENO,
			"-bash: syntax error near unexpected token `|'\n", 46);
	s->error_skip = 1;
	s->cmdretval = 2;
}

/* 
 * it reproduces the '-bash: cmd: command not found' message
 */

void	bash_error_cmdNotFound(t_shell *s, char *cmd)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	s->error_skip = 1;
	s->cmdretval = 127;
}

/* 
 * it reproduces the '-bash: Filename: error' message
 */

void	bash_error_wFilename(t_shell *s, char *file)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "No such file or directory\n", 26);
	s->error_skip = 1;
	s->cmdretval = errno;
}

/* syntax error when doublequotes or singlequotes are not closed up */

void	bash_syntaxError(t_shell *s)
{
	write(STDERR_FILENO, "bash: quotes: parsing error\n", 28);
	s->error_skip = 1;
}
