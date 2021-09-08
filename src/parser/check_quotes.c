/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/08 16:56:45 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int  is_specialchar(char c)
{
    return (c == SINGLEQTS || c == DOLLARSIGN);
}

/*
*  This function removes double quotes from the string
*  and replace $VAR with their value
*/

static void doubleqts_stringify(t_shell *s, char **arg, int i)
{
    int     j;
    int     k;
    char    *tmp;

    while (arg[i])  // singlequotes ascii code is 39
    {
        k = 0;
        j = -1;
        tmp = malloc(sizeof(char) * MAX + 1); // to check for leaks ?
        if (!tmp)
            malloxit();
        while (arg[i][++j])
            if ((arg[i][j] != DOUBLEQTS
                && !(arg[i][j] == BACKSLASH && arg[i][j + 1] && is_specialchar(arg[i][j + 1]))) // horrible, to refactor in a function is_specialchar
                || (j > 0 && arg[i][j] == DOUBLEQTS && arg[i][j - 1] == BACKSLASH))
                tmp[k++] = arg[i][j];
        tmp[k] = 0;
        str_replace(&arg[i], tmp);
        i++;
    }
    s->var.double_qts = 0;
}

/*
*  This function removes single quotes from the string
*/

static void singleqts_stringify(char **arg, int i)
{
    int     j;
    int     k;
    char    *tmp;
        
    while (arg[i])  // singlequotes ascii code is 39
    {
        k = 0;
        j = -1;
        tmp = malloc(sizeof(char) * MAX + 1); // to check for leaks ?
        if (!tmp)
            malloxit();
        while (arg[i][++j])
            if (arg[i][j] != SINGLEQTS)
                tmp[k++] = arg[i][j];
        tmp[k] = 0;
        str_replace(&arg[i], tmp);
        i++;
    }
}

void check_quotes(t_shell *s, char **arg, int i)
{
    if (starts_with("\'", arg[i]))
        s->var.single_qts = 1;
    else if (starts_with("\"", arg[i]))
        s->var.double_qts = 1;       
    if (s->var.single_qts)
        singleqts_stringify(arg, i);
    else if (s->var.double_qts)
        doubleqts_stringify(s, arg, i);
}