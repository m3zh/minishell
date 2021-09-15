/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:20:20 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 12:26:12 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* assistant to the exporter */

static void	assistant(t_shell *shell, char *str, char *var, int i)
{
	char	*newv;
	char	*value;

	value = ft_substr(str, i + 1, ft_strlen(str));
	if (!value)
		malloxit();
	newv = get_var(shell, var);
	if (newv == NULL)
		expoort(shell, str);
	else
	{
		if (!change_var(shell, var, value))
			exit(EXIT_FAILURE);
	}
	free(newv);
	free(value);
}

/* prepares the variables for the expoort function or the change_var */
/* function if the variable already exists */

void	exporter(t_shell *shell)
{
	int		i;
	char	*str;
	char	*var;

	i = starts_with("export ", shell->cmd[0]);
	while (shell->cmd[0] && ft_space(shell->cmd[0][i]))
		i += 1;
	str = ft_substr(shell->cmd[0], i - 1, ft_strlen(shell->cmd[0]));
	if (!str)
		malloxit();
	i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	var = ft_substr(str, 0, i);
	if (!var)
		malloxit();
	assistant(shell, str, var, i);
	free(var);
	free(str);
}
