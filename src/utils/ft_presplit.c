/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_presplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:15:12 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/19 21:57:40 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	skip_ahead2pipe(char *s, int i, int QUOTES)
{
	int	q;

	q = 1;
	i += 1;
	while (s[i])
	{
		if (is_quotes(s, i, QUOTES))
			q++;
		if ((s[i + 1] == PIPE && !(q & 1)) || !s[i + 1])
			break ;
		i++;
	}
	if (q & 1)
		bash_syntaxError();
	return (i);
}

char	*cpystr_wCharQuotes(char *s, int *i)
{
	int		end;
	int		start;
	char	*dst;

	dst = NULL;
	start = *i;
	while (s[*i])
	{
		if (s[*i] == SINGLEQTS)
			*i = skip_ahead2pipe(s, *i, SINGLEQTS);
		else if (s[*i] == DOUBLEQTS)
			*i = skip_ahead2pipe(s, *i, DOUBLEQTS);
		if (s[*i] == PIPE || !s[*i + 1])
		{
			end = *i;
			if (!s[*i + 1])
				end += 1;
			dst = ft_substr(s, start, end - start);
			if (!dst)
				malloxit();
			break ;
		}
		(*i)++;
	}		
	return (dst);
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
			i = skip_ahead2pipe(s, i, SINGLEQTS);
		else if (s[i] == DOUBLEQTS)
			i = skip_ahead2pipe(s, i, DOUBLEQTS);
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c
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
		arr[k] = cpystr_wCharQuotes(s, &i);
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
