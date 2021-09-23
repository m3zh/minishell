/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:50:03 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/21 08:54:49 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrchr(const char *s, int c)
{
	int	i;
	int	l;

	i = 0;
	l = (int)ft_strlen(s) + 1;
	while (--l >= 0)
	{
		if (s[l] == (char)c)
			return (i);
		++i;
	}
	return (i);
}
