/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:02:50 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/31 09:50:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
* unexpectedToken error displays when redirections (<,<<,>>,>)
* are not followed by a valid file, e.g. echo hello > | cat myfile
*/

void bash_error_unexpectedToken(t_shell *s)
{
    s->error_skip = 1;
    printf("-bash: syntax error near unexpected token `newline'\n");
    ft_exit(s);
}

/* 
* it reproduces the '-bash: Filename: error' message
*/

void bash_error_wFilename(t_shell *s, char *file)
{
    s->error_skip = 1;
    printf("-bash: %s: %s\n", file, strerror(errno));
    // ft_exit(s);
}
