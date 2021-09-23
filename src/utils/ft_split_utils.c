/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:54:37 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/20 22:57:15 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quotes(char *s, int i, int QUOTES)
{
	return (s[i] == QUOTES && s[i - 1] != BACKSLASH);
}

int	get_quoteCount(t_shell *sh, char *s, int i, int QUOTES)
{
	i += 1;
	while (s[i] && !is_quotes(s, i, QUOTES))
		i += 1;
	if (!s[i])
		bash_syntaxError(sh);
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
