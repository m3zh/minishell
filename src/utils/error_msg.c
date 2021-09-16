/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:02:50 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/16 13:14:34 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
 * unexpectedToken error displays when redirections (<,<<,>>,>)
 * are not followed by a valid file, e.g. echo hello > | cat myfile
 */

void	bash_error_unexpectedToken(t_shell *s)
{
	write(2, "-bash: syntax error near unexpected token `newline'\n", 52);
	s->cmdretval = 2;
}

/* 
 * it reproduces the '-bash: cmd: command not found' message
 */

void	bash_error_cmdNotFound(t_shell *s, char *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	s->cmdretval = 127;
}

/* 
 * it reproduces the '-bash: Filename: error' message
 */

void	bash_error_wFilename(t_shell *s, char *file)
{
	write(2, "bash: ", 6);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	perror("");
	s->cmdretval = errno;
}

/* syntax error when doublequotes or singlequotes are not closed up */

void	bash_syntaxError(void)
{
	write(2, "bash: quotes: parsing error\n", 28);
}
