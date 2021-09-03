/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 12:13:44 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// this function will probably need to be widen 
// with double and single quotes, $VAR etc. (into secondary functions such as check_dollar, check_quotes)



// static void preparsing(t_shell *s, int last)
// {
//     s->file.preparsing = 1;
//     if (s->pipelen > 1)
//         precheck_redir(s, last);
//     s->file.preparsing = 0;        
// }

int parse_shell(t_shell *shell, char *line, char **envp)
{
    int i;

    i = -1;
    init_shell(shell, envp);
    shell->cmd = ft_split(line, '|');
    if (!shell->cmd)
        return (ft_exit(shell));
    shell->pipelen = ft_tablen(shell->cmd);
    while(shell->cmd[++i])
    {
        shell->cmd[i] = ft_trim(shell->cmd[i]);
        if (!shell->cmd[i])
            return (ft_exit(shell)); // the free inside the function should be updated
    }
    // preparsing(shell, i - 1);
    return (0);
}
