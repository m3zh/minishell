/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 16:05:52 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// getoutfile and getinfile are 90% the same, could be merged into a single function
// waiting a bit to see if it's a good idea or there are exceptions to handle

static void singleqts_stringify(t_shell *s, char **arg, int i)
{
    int     j;
    int     k;
    char    *tmp;

    j = -1;
    k = 0;
    tmp = malloc(sizeof(char) * ft_strlen(arg[i]) + 1); // check for leaks ?
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

void check_quotes(t_shell *s, char **arg, int i, int j)
{
    (void)j;
    if (starts_with("\'", arg[i]))
        s->var.single_qts = 1;
    else if (starts_with("\"", arg[i]))
        s->var.double_qts = 1;       
    if (s->var.single_qts)
        singleqts_stringify(s, arg, i);
    // else if (s->var.double_qts)
    //     doubleqts_stringify(s, j);
}