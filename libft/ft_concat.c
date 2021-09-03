/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:48:18 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/03 18:17:24 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_concat(char **arg)
{
    int     i;
    int     l;
    char    *s;

    i = -1;
    l = 0;
    while (arg[++i])
        l += ft_strlen(arg[i]) + 1;
    i = -1;
    s = malloc(sizeof(char) * l);
    if (!s)
        return (NULL);
    s[l] = 0;
    while (arg[++i])
    {
        l = ft_strlen(arg[i]) + ft_strlen(s) + 1;
        ft_strcat(s, arg[i], l);
        ft_strcat(s, " ", l + 1);
    }
    return (s);
}