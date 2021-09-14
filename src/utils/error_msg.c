/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:02:50 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/14 18:49:26 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
* unexpectedToken error displays when redirections (<,<<,>>,>)
* are not followed by a valid file, e.g. echo hello > | cat myfile
*/

void bash_error_unexpectedToken(t_shell *s)
{
    printf("-bash: syntax error near unexpected token `newline'\n");
    s->cmdretval = 2;
}

/* 
* it reproduces the '-bash: cmd: command not found' message
*/

void bash_error_cmdNotFound(t_shell *s, char *cmd)
{
    printf("%s: command not found\n", cmd);
    s->cmdretval = 127;
}

/* 
* it reproduces the '-bash: Filename: error' message
*/

void bash_error_wFilename(t_shell *s, char *file)
{
    printf("-bash: %s: %s\n", file, strerror(errno));
    s->cmdretval = errno;
}

/* syntax error when doublequotes or singlequotes are not closed up */

void bash_syntaxError()
{
    printf("bash: quotes: parsing error\n");
}