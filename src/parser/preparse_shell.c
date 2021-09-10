/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/10 19:43:14 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void preparsing(t_shell *s, int last)
{
    // int i;

    // i = -1;
    // while (s->cmd[++i])
    // {
        
    // }
    s->file.preparsing = 1;
    if (s->pipelen > 1)
        precheck_redir(s, last);
    s->file.preparsing = 0;
}

int preparse_shell(t_shell *shell, char *line)
{
    // int     i;
    // char    *tmp;

    // i = -1;
    reinit_shell(shell);
    if (shell->cmd)
        free_arr(shell->cmd);
    shell->cmd = ft_split(line, '|');
    if (!shell->cmd)
        return (ft_exit(shell));
    shell->pipelen = ft_tablen(shell->cmd);
    // while(shell->cmd[++i]) // do not think this in necessary but waiting to confirm
    // {
    //     tmp = ft_trim(shell->cmd[i]);
    //     if (!tmp)
    //         return (ft_exit(shell));
    //     str_replace(&shell->cmd[i], tmp);
    //     if (!shell->cmd[i])
    //         return (ft_exit(shell)); // the free inside the function should be updated
    // }
    preparsing(shell, shell->pipelen - 1);
    free(line);
    return (0);
}
