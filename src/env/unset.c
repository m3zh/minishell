/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:38:24 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/06 13:09:29 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* mallocs each environment table line and copies the string over */
/* to the new table */

static void	tooler(char *str, char **tmp, int i, int *j)
{
	if (!(starts_with(str, environ[i])))
	{
		tmp[*j] = malloc(sizeof(char) * (ft_strlen(environ[i]) + 1));
		if (!tmp[*j])
			malloxit();
		ft_strlcpy(tmp[*j], environ[i], ft_strlen(environ[i]) + 1);
		*j += 1;
	}
}

/* iterates through the environment table and assigns the right values */

static void	assign(char *str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (environ[i])
	{
		tooler(str, tmp, i, &j);
		i += 1;
	}
	tmp[j] = 0;
	free(environ);
	environ = tmp;
}

/* mallocs the new environment table and calls the assign function */

void	unset(char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (environ[i])
		i += 1;
	tmp = malloc(sizeof(char *) * (i));
	if (!tmp)
		malloxit();
	assign(str, tmp);
}
