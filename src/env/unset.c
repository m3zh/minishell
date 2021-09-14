/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:38:24 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/13 18:57:31 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* if the var is not in env, we return */

static int	not_inEnv(t_shell *shell, char *var)
{
	int i;

	i = -1;
	while (shell->minienv[++i])
	{
		if (starts_with(var, shell->minienv[i]))
			return (0);
	}
	return (1);
}

/* mallocs each environment table line and copies the string over */
/* to the new table */

static void	tooler(t_shell *shell, char *str, char **tmp, int i, int *j)
{
	if (!(starts_with(str, shell->minienv[i])))
	{
		tmp[*j] = malloc(sizeof(char) * (ft_strlen(shell->minienv[i]) + 1));
		if (!tmp[*j])
			malloxit();
		ft_strlcpy(tmp[*j], shell->minienv[i], ft_strlen(shell->minienv[i]) + 1);
		*j += 1;
	}
}

/* iterates through the environment table and assigns the right values */

static void	assign(t_shell *shell, char *str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->minienv[i])
	{
		tooler(shell, str, tmp, i, &j);
		i += 1;
	}
	tmp[j] = 0;
	free_arr(shell->minienv);
	shell->minienv = malloc(sizeof(char *) * j);
	shell->minienv[--j] = 0;
	i = -1;
	while (++i < j)
	{
		shell->minienv[i] = ft_strdup(tmp[i]);
		if (!shell->minienv[i])
			malloxit();
	}	
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
