/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialsplit_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:54:37 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/15 13:17:19 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_specialchar(char c)
{
	return (c == SINGLEQTS
		|| c == DOLLARSIGN || c == DOUBLEQTS || c == BACKSLASH);
}

int	not_doublequote(char *s, int j)
{
	return ((is_specialchar(s[j]) && s[j - 1] == BACKSLASH)
		|| !is_specialchar(s[j]));
}

int	cpystr_wQuotes(char *s, char *arr, int i)
{
	int	j;

	j = 0;
	while (s[++i])
		if (not_doublequote(s, i))
			arr[j++] = s[i];
	arr[j] = '\0';
	return (i);
}

int	cpystr_wChar(char *s, char *arr, int i, int c)
{
	int	j;

	j = 0;
	while (s[i] && s[i] != c)
		arr[j++] = s[i++];
	arr[j] = '\0';
	return (i);
}
