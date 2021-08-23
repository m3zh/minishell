/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/16 15:11:32 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void get_outfile(t_shell *s, char **arg, int i)
{
    int file;

    file = i + 1;
    if (arg[file])
        s->outfile = ft_strdup(arg[file]);
    else
        return (bash_error_unexpectedToken(s));
    if (!s->outfile)
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

// static void append_outfile(t_shell *s, char **arg, int i)
// {
//     return ;
// }

// static void get_infile(t_shell *s, char **arg, int i)
// {
//     return ;
// }

// static void eof_stdin(t_shell *s, char **arg, int i)
// {
//     return ;
// }

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
            s->ow = 1;
        else if (!ft_strcmp(arg[i], ">>"))
            s->ap = 1;
        if (s->ow || s->ap)
            get_outfile(s, arg, i);          
        // else if (ft_strcmp(arg[i], "<"))
        //     get_infile(s, arg, i); 
        // else if (ft_strcmp(arg[i], "<<"))
        //     eof_stdin(s, arg, i);
    }
    return (arg);  
}