/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/02 15:22:09 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// getoutfile and getinfile are 90% the same, could be merged into a single function
// waiting a bit to see if it's a good idea or there are exceptions to handle

static void get_outfile(t_shell *s, char **arg, int i)
{
    int file;

    file = i + 1;
    if (arg[file])
        s->file.outfile = ft_strdup(arg[file]);
    else if (!s->file.preparsing)
        return (bash_error_unexpectedToken(s));
    if (!s->file.outfile)
        ft_exit(s);
    reset_string(arg, i);
    reset_string(arg, file);
    while (arg[++file])
    {
        arg[i] = ft_strdup(arg[file]);
        if (!arg[i])
            ft_exit(s);
        i++;
    }
    arg[file] = 0;
}

static void get_infile(t_shell *s, char **arg, int i)
{
    int file;

    file = i + 1;
    if (arg[file] && s->file.input)
        s->file.infile = ft_strdup(arg[file]);
    else if (arg[file] && s->file.here_doc)
        s->file.stopword = ft_strdup(arg[file]);
    else if (!s->file.preparsing)
        return (bash_error_unexpectedToken(s));
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
    return ;
}

char    **parse_arg(t_shell *s, int j)
{
    int i;
    char **arg;
    
    i = -1;
    arg = ft_split(s->cmd[j], ' ');
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
    return (arg);  
}