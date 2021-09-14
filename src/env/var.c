/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:52 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/09 10:23:40 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* returns 1 if the env table is alphabetically ranked, 0 if it isn't */

static int	ranked(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->e.env[i])
	{
		if (!sorter(shell->e.env[i - 1], shell->e.env[i]))
			return (0);
		i += 1;
	}
	return (1);
}

/* alphabetically ranks the environ array */

void	ranker(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (shell->e.env[i])
		i += 1;
	while (!ranked(shell))
	{
		j = 1;
		while (j < i)
		{
			if (!sorter(shell->e.env[j - 1], shell->e.env[j]))
			{
				tmp = shell->e.env[j - 1];
				shell->e.env[j - 1] = shell->e.env[j];
				shell->e.env[j] = tmp;
			}
			j += 1;
		}
	}
}


/* changes the value of the variable pointed to by *var to the value pointed */
/* to by *value */

int	change_var(t_shell *shell, char *var, char *value)
{
	int	i;

	i = 0;
	while (shell->e.env[i] && !(starts_with(var, shell->e.env[i])))
		i += 1;
	if (!shell->e.env[i])
		return (0);
	free(shell->e.env[i]);
	shell->e.env[i] = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(value) + 2));
	if (!shell->e.env[i])
		return (0);
	ft_strlcpy(shell->e.env[i], var, ft_strlen(var) + 1);
	ft_strlcat(shell->e.env[i], "=", ft_strlen(shell->e.env[i]) + 2);
	ft_strlcat(shell->e.env[i], value, ft_strlen(shell->e.env[i]) + ft_strlen(value) + 1);
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

char	*get_var(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (shell->e.env[i])
	{
		j = 0;
		while (shell->e.env[i][j] && shell->e.env[i][j] != '=')
			j += 1;
		var = ft_substr(shell->e.env[i], 0, j);
		if (!var)
			exit(EXIT_FAILURE);
		if (starts_with(str, var) && (int)ft_strlen(str) == j)
		{
			free(var);
			return (ft_substr(shell->e.env[i], j + 1, ft_strlen(shell->e.env[i])));
		}
		free(var);
		i += 1;
	}
	return (NULL);
}
