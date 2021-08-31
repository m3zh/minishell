/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:52 by maxdesall         #+#    #+#             */
/*   Updated: 2021/08/31 10:21:54 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* removes the name of the environment variable, and the "=" */

static int	var_strip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i - 1] != '=')
		i += 1;
	return (i);
}

/* returns a memory allocated string containing the value */
/* of the environment variable */

char	*get_var(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (shell->e.env[i])
	{
		if (comp(str, shell->e.env[i]))
			return (ft_substr(shell->e.env[i], var_strip(shell->e.env[i]), ft_strlen(shell->e.env[i])));
		i += 1;
	}
	return (NULL);
}
