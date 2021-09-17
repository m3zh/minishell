/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:45:52 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/17 16:46:44 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  is_dollar(char *s, int i)
{
    return ((i == 0 && s[i] == DOLLARSIGN)
			|| (i > 0 && s[i] == DOLLARSIGN && s[i - 1] != BACKSLASH));
}

// static int overwrite_dollarvalue(t_shell *s, char **tmp, char *value, int k)
// {
//     int     start;
//     char    *var;

//     var = get_var(s, value);
//     if (var)
//     {
//         start = -1;
//         while (var[++start])
//             tmp[k++] = var[start];
//     }
//     free(value);
//     free(var);
//     printf("var %s\n",*tmp);
//     return (k);
// }

static void doubleqts_stringify(t_shell *s, char **arg, int i)
{
    int     j;
    int     k;
    int     start;
    char    *tmp;
    char    *value;
    char    *var;

    while (arg[i])
    {
        k = 0;
        j = 0;
        tmp = malloc(sizeof(char) * MAX + 1);
        if (!tmp)
            malloxit();
        while (arg[i][j++])
        {
            if (is_dollar(arg[i], j))
            {
                j++;
                start = j;
                while (arg[i][j] && ft_isalnum(arg[i][j]))
                    j++;
                value = ft_substr(arg[i], start, j - start);
                if (!value)
                    malloxit();
                var = get_var(s, value);
                if (var)
                {
                    start = -1;
                    while (var[++start])
                        tmp[k++] = var[start];
                }
                free(value);
                free(var);
                j--;
            }
            else if (valid_dbquote(arg[i], j, DOUBLEQTS))
                tmp[k++] = arg[i][j];
        }
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