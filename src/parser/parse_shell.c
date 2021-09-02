/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/02 14:50:07 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// this function will probably need to be widen 
// with double and single quotes, $VAR etc. (into secondary functions such as check_dollar, check_quotes)

static void check_redir(t_shell *s, int last)
{
    int i;
    char **arg;
    
    i = -1;
    arg = ft_split(s->cmd[last], ' ');
    if (!arg)
        ft_exit(s);
    while (arg[++i])
    {
        if (!ft_strcmp(arg[i], ">"))
            s->file.ow = 1;
        else if (!ft_strcmp(arg[i], ">>"))
            s->file.ap = 1;        
        else if (!ft_strcmp(arg[i], "<"))
            s->file.input = 1; 
        else if (!ft_strcmp(arg[i], "<<"))
            s->file.here_doc = 1;
        if (s->file.ow || s->file.ap)
            get_outfile(s, arg, i);
        else if (s->file.input || s->file.here_doc)
            get_infile(s, arg, i);
    }
}

static void preparsing(t_shell *s, int last)
{
    if (s->len > 1)
        check_redir(s, last);
}

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
    preparsing(shell, i - 1);
    return (0);
}
