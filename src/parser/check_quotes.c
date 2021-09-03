/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:31:59 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 13:13:55 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// getoutfile and getinfile are 90% the same, could be merged into a single function
// waiting a bit to see if it's a good idea or there are exceptions to handle

// static void doubleqts_stringify(t_shell *s, int j)
// {
//     (void)j;
//     s->var.double_qts = 0;
// }

static void singleqts_stringify(t_shell *s, int j)
{
    int     i;
    int     k;
    char    *tmp;

    i = -1;
    k = 0;
    tmp = malloc(sizeof(char) * ft_strlen(s->cmd[j])); // check for leaks ?
    if (!tmp)
        malloxit();
    while (s->cmd[j] && s->cmd[j][++i])  // singlequotes ascii code is 27
    {
        printf("here");
        if (s->cmd[j][i] != SINGLEQTS)
            tmp[k++] = s->cmd[j][i];
    }
    tmp[k] = 0;
    free(s->cmd[j]);
    s->cmd[j] = ft_strdup(tmp);
    if (!s->cmd[j])
        malloxit();
    free(tmp);        
    s->var.single_qts = 0;
}

void check_quotes(t_shell *s, char **arg, int i, int j)
{
    if (starts_with("\'", arg[i]))
        s->var.single_qts = 1;
    else if (starts_with("\"", arg[i]))
        s->var.double_qts = 1;       
    if (s->var.single_qts)
        singleqts_stringify(s, j);
    // else if (s->var.double_qts)
    //     doubleqts_stringify(s, j);
}