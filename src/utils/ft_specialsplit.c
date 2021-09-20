/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:15:12 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/20 12:07:35 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cpystr_wQuotes(char *s, char *arr, int i, int Q)
{
	int	j;

	j = 0;
	arr[j++] = s[i];
	while (s[++i] && valid_dbquote(s, i, Q))
		if (Q == SINGLEQTS || valid_dbquote(s, i, Q))
			arr[j++] = s[i];
	arr[j] = s[i];
	arr[j + 1] = '\0';
	return (i + 1);
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

static int	word_count(t_shell *sh, char *s, char c)
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
		{
			i = get_quoteCount(sh, s, i, SINGLEQTS);
			count++;
		}
		else if (s[i] == DOUBLEQTS)
		{
			i = get_quoteCount(sh, s, i, DOUBLEQTS);
			count++;
		}
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
		arr[k] = (char *)malloc(sizeof(char) * (LEN + 1));
		if (!arr[k])
		{
			free_arr(arr);
			return (NULL);
		}
		while (s[i] && s[i] == c)
			i++;
		if ((s[i] && s[i] == SINGLEQTS))
			i = cpystr_wQuotes(s, arr[k], i, SINGLEQTS);
		else if ((s[i] && s[i] == DOUBLEQTS))
			i = cpystr_wQuotes(s, arr[k], i, DOUBLEQTS);
		else
			i = cpystr_wChar(s, arr[k], i, c);
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_specialsplit(t_shell *sh, char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(sh, s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (fill_arr(words, s, c, arr));
}
