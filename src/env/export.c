/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:28:31 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/13 12:05:41 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* returns 1 if all the characters until j are equal between the two strings */

int	equal(t_shell *shell, char *str, int i, int j)
{
	int	k;

	k = 0;
	while (k < j && shell->minienv[i][k] && str[k] && shell->minienv[i][k] != '=' && str[k] != '=')
	{
		if (str[k] != shell->minienv[i][k])
			return (0);
		k += 1;
	}
	return (1);
}

/* returns the line at which the new environment variable should be placed */

int	alpharank(t_shell *shell, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->minienv[i] && str[0] > shell->minienv[i][0])
		i += 1;
	while (j < (int)ft_strlen(str) && shell->minienv[i])
	{
		while (equal(shell, str, i, j) && str[j] > shell->minienv[i][j])
			i += 1;
		j += 1;
	}
	return (i);
}

/* allocates memory for each line of the environment table and copies */
/* the content over from the previous table to the new one */

static void	tooler(t_shell *shell, char **tmp, int i, int j)
{
	tmp[j] = malloc(sizeof(char) * (ft_strlen(shell->minienv[i]) + 1));
	if (!tmp[j])
		malloxit();
	ft_strlcpy(tmp[j], shell->minienv[i], ft_strlen(shell->minienv[i]) + 1);
}

/* iterates through the environment table and assigns the right values */

static void	assign(t_shell *shell, char *str, char **tmp)
{
	int	i;
	int	j;
	int	alpha;

	i = 0;
	j = 0;
	alpha = alpharank(shell, str);
	while (shell->minienv[i])
	{
		if (i != alpha)
		{
			tooler(shell, tmp, i, j);
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

void	expoort(t_shell *shell, char *str)
{
	int		i;
	char	**tmp;

	i = ft_tablen(shell->minienv);
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		malloxit();
	assign(shell, str, tmp);
	tmp[i + 1] = 0;
	free_arr(shell->minienv);
	shell->minienv = malloc(sizeof(char *) * (i + 2));
	shell->minienv[i + 1] = 0;
	while (i >= 0)
	{
		shell->minienv[i] = ft_strdup(tmp[i]);
		if (!shell->minienv[i])
			malloxit();
		i--;
	}
	free_arr(tmp);
}
