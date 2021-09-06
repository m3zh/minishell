/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:28:31 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/06 14:31:33 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* returns 1 if all the characters until j are equal between the two strings */

int	equal(char *str, int i, int j)
{
	int	k;

	k = 0;
	while (k < j && environ[i][k] && str[k])
	{
		if (str[k] != environ[i][k])
			return (0);
		k += 1;
	}
	return (1);
}

/* returns the line at which the new environment variable should be placed */

int	alpharank(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (environ[i] && str[0] > environ[i][0])
		i += 1;
	while (j < (int)ft_strlen(str) && environ[i])
	{
		while (equal(str, i, j) && str[j] > environ[i][j])
			i += 1;
		j += 1;
	}
	return (i);
}

/* allocates memory for each line of the environment table and copies */
/* the content over from the previous table to the new one */

static void	tooler(char **tmp, int i, int j)
{
	tmp[j] = malloc(sizeof(char) * (ft_strlen(environ[i]) + 1));
	if (!tmp[j])
		malloxit();
	ft_strlcpy(tmp[j], environ[i], ft_strlen(environ[i]) + 1);
}

/* iterates through the environment table and assigns the right values */

static void	assign(char *str, char **tmp)
{
	int	i;
	int	j;
	int	alpha;

	i = 0;
	j = 0;
	alpha = alpharank(str);
	while (environ[i])
	{
		if (i != alpha)
		{
			tooler(tmp, i, j);
			i += 1;
		}
		else
		{
			alpha = -1;
			tmp[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!tmp[j])
				malloxit();
			ft_strlcpy(tmp[j], str, ft_strlen(str) + 1);
		}
		j += 1;
	}
}

/* mallocs the new environment table and calls the assign function */

void	expoort(char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (environ[i])
		i += 1;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		malloxit();
	assign(str, tmp);
	tmp[i + 1] = 0;
	free(environ);
	environ = tmp;
}
