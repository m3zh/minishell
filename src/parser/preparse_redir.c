/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:21:00 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/02 16:25:14 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **pre_infile(t_shell *s, char **arg, int i)
{
    int     file;

    file = i + 1;
    if (arg[file] && s->file.input)
        s->file.infile = ft_strdup(arg[file]);
    else if (arg[file] && s->file.here_doc)
        s->file.stopword = ft_strdup(arg[file]);
    // else
    //     return (bash_error_unexpectedToken(s)); // don't think I need it here
    if (!s->file.infile && !s->file.stopword) // check leaks
        ft_exit(s);
    reset_string(arg, i);
    reset_string(arg, file);
    while (arg[++file])
    {
        s->file.more = 1;
        arg[i] = ft_strdup(arg[file]);
        if (!arg[i])
            ft_exit(s);
        i++;
    }
    arg[file] = 0;
    return (arg);
}

void check_redir(t_shell *s, int last)
{
    int i;
    char **arg;
    
    i = -1;
    arg = ft_split(s->cmd[last], ' ');
    if (!arg)
        ft_exit(s);
    while (arg[++i])
    {
        if (!ft_strcmp(arg[i], "2>")) // to be handled
            s->file.lastErr = 1;
        else if (!ft_strcmp(arg[i], ">&")) // to be handled
            s->file.allErr = 1;        
        else if (!ft_strcmp(arg[i], "<"))
            s->file.input = 1; 
        else if (!ft_strcmp(arg[i], "<<"))
            s->file.here_doc = 1;
        if (s->file.input || s->file.here_doc)
        {
            arg = pre_infile(s, arg, i);
            free(s->cmd[last]);
            s->cmd[last] = ft_concat(arg);
        }  
    }
 
}