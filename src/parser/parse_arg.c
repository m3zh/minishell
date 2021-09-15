/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/15 10:52:08 by mlazzare         ###   ########.fr       */
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
        swap_file(&s->file.outfile, arg, file);
    else if (!s->file.preparsing)
        return (bash_error_unexpectedToken(s));
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
    s->check.redir = 1;
}

static void get_infile(t_shell *s, char **arg, int i)
{
    int file;

    file = i + 1;
    if (arg[file] && s->file.input)
        swap_file(&s->file.infile, arg, file);
    else if (arg[file] && s->file.here_doc)
        swap_file(&s->file.stopword, arg, file);
    else if (!s->file.preparsing)
        return (bash_error_unexpectedToken(s));
    reset_string(arg, i);
    reset_string(arg, file);
    if (arg[file + 1] && !ft_strcmp(arg[file + 1], "<"))
        get_infile(s, arg, file + 1);
    while (arg[++file])
    {
        s->file.more = 1;
        arg[i] = ft_strdup(arg[file]);
        if (!arg[i])
            ft_exit(s);
        i++;
    }
    arg[file] = 0;
    s->check.redir = 1;
}

static void check_redir(t_shell *s, char **arg, int i)
{
    if (s->var.single_qts || s->var.double_qts)
        return ;
    if (!ft_strcmp(arg[i], ">"))
        s->file.ow = 1;
    else if (!ft_strcmp(arg[i], ">>"))
        s->file.ap = 1;        
    else if (!ft_strcmp(arg[i], "<"))
        s->file.input = 1; 
    else if (!ft_strcmp(arg[i], "<<"))
        s->file.here_doc = 1;
    // else if (!ft_strcmp(arg[i], "2>")) // this is not required so we don't handle it
    //         s->file.err = 1;
    // else if (!ft_strcmp(arg[i], "&>")
    //         || !ft_strcmp(arg[i], ">&")) 
    //         s->file.err_out = 1;  
    if ((s->file.ow || s->file.ap) && !s->file.outfile)
        get_outfile(s, arg, i);
    else if ((s->file.input && !s->file.infile)
        || (s->file.here_doc && !s->file.stopword))
        get_infile(s, arg, i);
    // else if (s->file.err || s->file.err_out) // this is not required so we don't handle it
    //     get_errfile(s, arg, i);
}

char    **parse_arg(t_shell *s, int j)
{
    int i;
    char **arg;
    
    i = -1;
    arg = ft_specialsplit(s->cmd[j], ' '); // does not slpit on ' ' if echo "word          word"
    if (!arg)
        ft_exit(s);
    while (arg[++i])
    {
        // check_quotes(s, arg, i);
        check_echo(s, arg, i);
        check_redir(s, arg, i);
        // check_user(s, arg, i);
    }
    s->var.single_qts = 0; // reset shell
    return (arg);  
}