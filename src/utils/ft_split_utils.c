/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:54:37 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/17 13:47:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quotes(char *s, int i, int QUOTES)
{
	return ((s[i] == QUOTES && s[i - 1] != BACKSLASH)
		|| (s[i] == QUOTES && !s[i + 1]));
}

int	get_quoteCount(char *s, int i, int QUOTES, int *count)
{
	i++;
	while (s[i] && !is_quotes(s, i, QUOTES))
		i++;
	if (!s[i])
		bash_syntaxError();
	*count += 1;
	return (i);
}

static int	is_specialchar(char c)
{
	return (c == SINGLEQTS || c == DOUBLEQTS || c == BACKSLASH);
}

int	not_doublequote(char *s, int j)
{
	return ((is_specialchar(s[j]) && s[j - 1] == BACKSLASH)
		|| !is_specialchar(s[j])
		|| (s[j] == BACKSLASH && s[j + 1] == DOLLARSIGN));
}

int	valid_dbquote(char *s, int j, int Q)
{
	return (((s[j] == DOUBLEQTS || s[j] == BACKSLASH) && s[j - 1] == BACKSLASH)
		|| !(s[j] == Q || s[j] == BACKSLASH)
		|| (s[j] == BACKSLASH && s[j + 1] == DOLLARSIGN));
}

