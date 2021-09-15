/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:15:12 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 13:15:31 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_quotes(char *s, int i, int QUOTES)
{
	return (s[i] == QUOTES
		&& (s[i - 1] != BACKSLASH || !s[i + 1]));
}

static int	get_quoteCount(char *s, int i, int QUOTES, int *count)
{
	i++;
	while (s[i] && !is_quotes(s, i, QUOTES))
		i++;
	if (!s[i])
		bash_syntaxError(); // need to add free shell?
	*count += 1;
	return (i);
}

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == SINGLEQTS)
			i = get_quoteCount(s, i, SINGLEQTS, &count);
		else if (s[i] == DOUBLEQTS)
			i = get_quoteCount(s, i, DOUBLEQTS, &count);
		else if ((s[i] != c && s[i + 1] == c) || (s[i] != c
				&& s[i + 1] == '\0'))
			count++;
	}
	return (count);
}

static char	**fill_arr(int words, char *s, char c, char **arr)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		arr[k] = (char *)malloc(sizeof(char) * LEN);
		if (!arr[k])
		{
			free_arr(arr);
			return (NULL);
		}
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] == SINGLEQTS)
			i = cpystr_wQuotes(s, arr[k], i);
		else if (s[i] && s[i] == DOUBLEQTS)
			i = cpystr_wQuotes(s, arr[k], i);
		else
			i = cpystr_wChar(s, arr[k], i, c);
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_specialsplit(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (fill_arr(words, s, c, arr));
}
