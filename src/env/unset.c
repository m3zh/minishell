/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:38:24 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/23 13:50:58 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* if the var is not in env, we return */

static int	not_inEnv(t_shell *shell, char *var)
{
	int	i;

	i = -1;
	while (shell->minienv[++i])
	{
		if (starts_with(var, shell->minienv[i]))
			return (0);
	}
	return (1);
}

/* iterates through the environment table and assigns the right values */

static void	assign(t_shell *shell, char *str, char **tmp)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (shell->minienv[++i])
	{
		if (!starts_with(str, shell->minienv[i]))
		{
			tmp[++j] = ft_strdup(shell->minienv[i]);
			if (!tmp[j])
				malloxit();
		}
	}
	tmp[++j] = 0;
	free_arr(shell->minienv);
	shell->minienv = malloc(sizeof(char *) * MAX);
	i = -1;
	while (tmp[++i] && i < j)
	{
		shell->minienv[i] = ft_strdup(tmp[i]);
		if (!shell->minienv[i])
			malloxit();
	}
	shell->minienv[i] = 0;
}

/* mallocs the new environment table and calls the assign function */

void	unset(t_shell *shell, char *str)
{
	int		i;
	char	**tmp;

	if (not_inEnv(shell, str))
		return ;
	i = ft_tablen(shell->minienv);
	tmp = malloc(sizeof(char *) * i);
	if (!tmp)
		malloxit();
	assign(shell, str, tmp);
	free_arr(tmp);
}
