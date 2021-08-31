/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/10 15:17:43 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int parse_shell(t_shell *shell, char *line, char **envp)
{
    int i;

    i = -1;
    init_shell(shell, envp);
    shell->cmd = ft_split(line, '|');
    if (!shell->cmd)
        return (ft_exit(shell));
    shell->len = ft_tablen(shell->cmd);
    while(shell->cmd[++i])
    {
        shell->cmd[i] = ft_trim(shell->cmd[i]);
        if (!shell->cmd[i])
            return (ft_exit(shell)); // the free inside the function should be updated
    }
    return (0);
}
