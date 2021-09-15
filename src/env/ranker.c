/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:36:42 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 12:38:35 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* returns 1 if the env table is alphabetically ranked, 0 if it isn't */

static int	ranked(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->minienv[i])
	{
		if (!sorter(shell->minienv[i - 1], shell->minienv[i]))
			return (0);
		i += 1;
	}
	return (1);
}

/* assistant to the ranker */

static void	assistant(t_shell *shell, int j)
{
	char	*tmp;

	tmp = ft_strdup(shell->minienv[j - 1]);
	if (!tmp)
		malloxit();
	free(shell->minienv[j - 1]);
	shell->minienv[j - 1] = ft_strdup(shell->minienv[j]);
	if (!shell->minienv[j - 1])
		malloxit();
	free(shell->minienv[j]);
	shell->minienv[j] = ft_strdup(tmp);
	if (!shell->minienv[j])
		malloxit();
	free(tmp);
}

/* alphabetically ranks the environ array */

void	ranker(t_shell *shell)
{
	int		i;
	int		j;

	j = 0;
	i = ft_tablen(shell->minienv);
	while (!ranked(shell))
	{
		j = 1;
		while (j < i)
		{
			if (!sorter(shell->minienv[j - 1], shell->minienv[j]))
				assistant(shell, j);
			j += 1;
		}
	}
}
