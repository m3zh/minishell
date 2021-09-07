/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:52 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/06 15:39:55 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* returns 1 if the environ table is alphabetically ranked, 0 if it isn't */

static int	ranked(void)
{
	int	i;

	i = 1;
	while (environ[i])
	{
		if (alpharank(environ[i - 1]) > alpharank(environ[i]))
			return (0);
		i += 1;
	}
	return (1);
}

/* alphabetically ranks the environ array */

void	ranker(void)
{
	int		i;
	int		j;
	char	*str1;
	char	*str2;

	i = 0;
	j = 0;
	while (environ[i])
		i += 1;
	while (!ranked())
	{
		j = 1;
		while (j < i)
		{
			if (alpharank(environ[j - 1]) > alpharank(environ[j]))
			{
				str1 = ft_strdup(environ[j - 1]);
				str2 = ft_strdup(environ[j]);
				free(environ[j - 1]);
				free(environ[j]);
				environ[j - 1] = str2;
				environ[j] = str1;
			}
			j += 1;
		}
	}
}


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

char	*get_val(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[j] && ((str[j] >= 9 && str[j] <= 13) || str[j] == ' '))
		j += 1;
	i = j;
	while (str[i] && str[i] != '=')
		i += 1;
	return (ft_substr(str, j, i));
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
