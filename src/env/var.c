/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:52 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/01 17:22:54 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_var(char *var, char *value)
{
	int	i;

	i = 0;
	while (environ[i] && !(comp(var, environ[i])))
		i += 1;
	if (!environ[i])
		return (0);
	free(environ[i]);
	environ[i] = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
	if (!environ[i])
		return (0);
	strlcpy(environ[i], var, ft_strlen(var) + 1);
	strlcat(environ[i], "=", ft_strlen(environ[i]) + 2);
	strlcat(environ[i], value, ft_strlen(environ[i]) + ft_strlen(value) + 1);
	return (1);
}

/* removes the name of the environment variable, and the "=" */

static int	var_strip(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i - 1] != '=')
		i += 1;
	return (i);
}

/* returns a memory allocated string containing the value */
/* of the environment variable */

char	*get_var(char *str)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (comp(str, environ[i]))
			return (ft_substr(environ[i], var_strip(environ[i]), ft_strlen(environ[i])));
		i += 1;
	}
	return (NULL);
}
