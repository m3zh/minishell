/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_presplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:15:12 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/16 15:54:05 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_quoteCounter(char *s, int i, int QUOTES)
{
	i += 1;
	while (s[i] && !is_quotes(s, i, QUOTES))
		i += 1;
	if (!s[i])
		bash_syntaxError();
	return (i);
}

int	cpystr_wCharQuotes(char *s, char *arr, int i, int c)
{
	int	j;
	int	q;

	j = 0;
	q = 0;
	while (s[i] && s[i] != c && !(q & 1))
	{
		if (s[i - 1] != BACKSLASH && (s[i] == DOUBLEQTS || s[i] == SINGLEQTS))
			q++;
		arr[j++] = s[i++];
	}		
	arr[j] = '\0';
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
			i = get_quoteCounter(s, i, SINGLEQTS);
		else if (s[i] == DOUBLEQTS)
			i = get_quoteCounter(s, i, DOUBLEQTS);
		else if ((s[i] != c && s[i + 1] == c) || (s[i] != c
				&& s[i + 1] == '\0'))
			count++;
	}
	// printf("count %d\n", count);
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
		i = cpystr_wCharQuotes(s, arr[k], i, c);
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_presplit(char *s, char c)
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
