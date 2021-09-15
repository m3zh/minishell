/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:04:29 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 09:04:45 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_dbquotes(char *s, int i)
{
	return (s[i] == DOUBLEQTS
		&& (s[i - 1] != BACKSLASH || !s[i + 1]));
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
		if (s[i] == DOUBLEQTS) // if you find a quote
		{
			i++;
			while (s[i] && !is_dbquotes(s, i))
				i++;
			if (!s[i])
				bash_syntaxError(); // need to add free shell?
			count++;
		}
		else if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
	return (count);
}

// static int	words_len(char *s, char c, int i)
// {
// 	int l;

// 	l = 0;
// 	while (s[i] && s[i] == c)
// 		i++;
// 	while (s[i] && s[i++] != c)
// 		l++;
// 	return (l);
// }

static char	**fill_arr(int words, char *s, char c, char **arr)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (k < words)
	{
		j = 0;
		if (!(arr[k] = (char *)malloc(sizeof(char) * LEN)))
		{
			free_arr(arr);
			return (NULL);
		}
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] == DOUBLEQTS)
		{
			while (s[++i])
				if (not_doublequote(s, i))
					arr[k][j++] = s[i];
		}
		else
		{
			while (s[i] && s[i] != c)
				arr[k][j++] = s[i++];
		}
		arr[k][j] = '\0';
		k++;
	}
	arr[k] = 0;
	return (arr);
}

char		**ft_specialsplit(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, s, c, arr);
	return (arr);
}
