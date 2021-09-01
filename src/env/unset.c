/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:38:24 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/01 16:10:51 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset(char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (environ[i])
		i += 1;
	tmp = malloc(sizeof(char *) * (i));
	if (!tmp)
		return ;
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (!(comp(str, environ[i])))
		{
			tmp[j] = malloc(sizeof(char) * (ft_strlen(environ[i]) + 1));
			if (!tmp[j])
				return ;
			ft_strlcpy(tmp[j], environ[i], ft_strlen(environ[i]) + 1);
			j += 1;
		}
		i += 1;
	}
	tmp[j] = 0;
	free(environ);
	environ = tmp;
}
