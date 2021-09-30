/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:54:37 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/30 12:22:00 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			i += 1;
			while (s[i] && s[i] != '"')
				i += 1;
		}
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
	}
	return (count);
}

static int	words_len(const char *s, char c, int i)
{
	int	l;

	l = 0;
	while (s[i] && s[i] == c)
		i += 1;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i += 1;
			while (s[i] && s[i++] != '"')
				l += 1;
		}
		else if (s[i] != c)
		{
			i += 1;
			l += 1;
		}
		else if (s[i] == c)
			break ;
	}
	return (l);
}

static char	**freetab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static char	**fill_arr(int words, const char *s, char c, char **arr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = -1;
	while (++k < words)
	{
		j = 0;
		arr[k] = (char *)malloc(sizeof(char) * (words_len(s, c, i) + 1));
		if (!arr[k])
			return (freetab(arr));
		while (s[i] && s[i] == c)
			i += 1;
		while (s[i])
		{
			if (s[i] == '"')
			{
				i += 1;
				while (s[i] && s[i] != '"')
					arr[k][j++] = s[i++];
				i += 1;
			}
			else if (s[i] != c)
				arr[k][j++] = s[i++];
			else if (s[i] == c)
				break ;
		}
		arr[k][j] = '\0';
	}
	arr[k] = 0;
	return (arr);
}

char	**ft_split_quotes(char const *s, char c)
{
	int		words;
	char	**arr;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, s, c, arr);
	return (arr);
}
