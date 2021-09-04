/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:52 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/04 07:33:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* changes the value of the variable pointed to by *var to the value pointed */
/* to by *value */

int	change_var(char *var, char *value)
{
	int	i;

	i = 0;
	while (environ[i] && !(starts_with(var, environ[i])))
		i += 1;
	if (!environ[i])
		return (0);
	free(environ[i]);
	environ[i] = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
	if (!environ[i])
		return (0);
	ft_strlcpy(environ[i], var, ft_strlen(var) + 1);
	ft_strlcat(environ[i], "=", ft_strlen(environ[i]) + 2);
	ft_strlcat(environ[i], value, ft_strlen(environ[i]) + ft_strlen(value) + 1);
	return (1);
}

/* returns a memory allocated string containing the value */
/* of the environment variable */

char	*get_var(char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '=')
			j += 1;
		var = ft_substr(environ[i], 0, j);
		if (starts_with(str, var))
		{
			free(var);
			return (ft_substr(environ[i], j + 1, ft_strlen(environ[i])));
		}
		free(var);
		i += 1;
	}
	return (NULL);
}
