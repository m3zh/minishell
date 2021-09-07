/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:44:55 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/07 17:37:31 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void    ctrl_c(int sig)
{
    if (sig == SIGINT)
        exit(1);    
}

void    shell_signal()
{
    signal(SIGINT, ctrl_c);
}