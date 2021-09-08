/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:44:55 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/08 11:35:38 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void    ctrl_slash(int sig)
// {
//     return ;   
// }

static void    ctrl_d(int sig)
{
    if (sig == SIGKILL)
        printf("exit\n");
    exit(EXIT_SUCCESS);  
}

static void    ctrl_c(int sig)
{
    if (sig == SIGINT)
        exit(1);    
}

void    shell_signal()
{
    signal(SIGINT, ctrl_c);
    signal(SIGINT, ctrl_d);
    // signal(SIGINT, ctrl_slash);
}