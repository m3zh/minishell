/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/06 12:49:03 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *dollar2value(char *s, int start, int size)
{
    char    *var;
    char    *var_name;
    
    var_name = ft_substr(s, start, size);
    if (!var_name)
        malloxit();
    var = get_var(var_name);
    if (!var)
    {
        var = ft_strdup("");
        if (!var)
            malloxit();            
    }
    free(var_name);
    return (var);
}

/*
*  This function removes double quotes from the string
*  and replace $VAR with their value
*/

static void doubleqts_stringify(t_shell *s, char **arg, int i)
{
    int     j;
    int     k;
    int     start;
    char    *tmp;
    char    *var;

    j = -1;
    k = 0;
    tmp = malloc(sizeof(char) * MAX + 1); // to check for leaks ?
    if (!tmp)
        malloxit();
    while (arg[i][++j])  // doublequotes ascii code is 34
    {
        if (arg[i][j] == DOLLARSIGN && (j == 0 || arg[i][j - 1] != BACKSLASH))
        {
            j++;
            start = j;
            while (arg[i][j]
                && !ft_space(arg[i][j]) && arg[i][j] != DOUBLEQTS)
                j++;
            var = dollar2value(arg[i], start, j - start);
            start = 0;
            while (tmp[k] && var[start])
                tmp[k++] = var[start++];
            free(var);
            j--;
        }
        else if (arg[i][j] != DOUBLEQTS ||
                (j > 0 && arg[i][j - 1] == BACKSLASH
                && arg[i][j] == DOUBLEQTS))
            tmp[k++] = arg[i][j];
    }
    tmp[k] = 0;
    str_replace(&arg[i], tmp);
    // if (arg[i])
    //     free(arg[i]);
    // arg[i] = ft_strdup(tmp);
    // if (!arg[i])
    //     malloxit();
    // free(tmp);  
    s->var.double_qts = 0;
}

/*
*  This function removes single quotes from the string
*/

static void singleqts_stringify(t_shell *s, char **arg, int i)
{
    int     j;
    int     k;
    char    *tmp;

    j = -1;
    k = 0;
    tmp = malloc(sizeof(char) * ft_strlen(arg[i]) + 1); // to check for leaks ?
    if (!tmp)
        malloxit();
    while (arg[i][++j])  // singlequotes ascii code is 39
    {
        if (arg[i][j] != SINGLEQTS)
            tmp[k++] = arg[i][j];
    }
    tmp[k] = 0;
    str_replace(&arg[i], tmp);
    // free(arg[i]);
    // arg[i] = ft_strdup(tmp);
    // if (!arg[i])
    //     malloxit();
    // free(tmp);
    (void)s;
}

void check_quotes(t_shell *s, char **arg, int i)
{
    if (starts_with("\'", arg[i]))
        s->var.single_qts = 1;
    else if (starts_with("\"", arg[i]))
        s->var.double_qts = 1;       
    if (s->var.single_qts)
        singleqts_stringify(s, arg, i);
    else if (s->var.double_qts)
        doubleqts_stringify(s, arg, i);
}

void check_echo(t_shell *s, char **arg, int i)
{
    char *tmp;

    if (s->var.single_qts || s->var.double_qts)
        return ;
    if (!ft_strcmp(arg[0], "echo") && starts_with("$", arg[i]))
    {
        tmp = dollar2value(arg[i], 1, sizeof(arg[i]));
        if (!tmp)
            malloxit();
        str_replace(&arg[i], tmp);
    }
}