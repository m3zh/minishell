/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:54:37 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/30 19:22:27 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX 1000

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

static char	**freetab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static char	*get_line(const char *s, int *i, char c)
{
	int		j;
	char	*line;

	j = 0;
	line = (char *)malloc(sizeof(char) * (MAX + 1));
	if (!line)
		return (NULL);
	while (s[(*i)] && s[(*i)] == c)
		(*i) += 1;
	while (s[(*i)] && s[(*i)] != c)
	{
		if (s[(*i)] == '"')
		{
			(*i) += 1;
			while (s[(*i)] && s[(*i)] != '"')
				line[j++] = s[(*i)++];
			(*i) += 1;
		}
		else if (s[(*i)] != c)
			line[j++] = s[(*i)++];
	}
	line[j] = '\0';
	return (line);
}

static char	**fill_arr(int words, const char *s, char c, char **arr)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	arr[0] = 0;
	while (++k < words)
	{
		arr[k] = get_line(s, &i, c);
		if (!arr[k])
			return (freetab(arr));
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
