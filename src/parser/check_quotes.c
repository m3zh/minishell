/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 18:27:19 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
    char    *var_name;
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
            start = j + 1;
            while (arg[i][j] && !ft_space(arg[i][j]))
                j++;
            var_name = ft_substr(arg[i], start, j);
            if (!var_name)
                malloxit();
            var = get_var(var_name);
            if (!var)
            {
                var = ft_strdup("");
                if (!var)
                    malloxit();            
            }
            while (tmp[k] && *var)
                tmp[k++] = *var++;
            j--;
        }
        else if (arg[i][j] != DOUBLEQTS ||
            (j > 0 && arg[i][j - 1] == BACKSLASH && arg[i][j] == DOUBLEQTS))
            tmp[k++] = arg[i][j];
    }
    tmp[k] = 0;
    if (arg[i])
        free(arg[i]);
    arg[i] = ft_strdup(tmp);
    if (!arg[i])
        malloxit();
    free(tmp);  
    s->var.single_qts = 0;
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
    free(arg[i]);
    arg[i] = ft_strdup(tmp);
    if (!arg[i])
        malloxit();
    free(tmp);        
    s->var.single_qts = 0;
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