/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:13:13 by maxdesall         #+#    #+#             */
/*   Updated: 2021/08/31 17:23:41 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exporter(char *str)
{
	int		i;
	int		tmp;
	char	*var;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	if (str[i] == '=')
	{
		tmp = i;
		i -= 1;
		while (str[i] >= 65 && str[i] <= 90 && i > 0)
			i -= 1;
		var = ft_substr(str, i, tmp);
		i = tmp + 1;
		while (str[i] && str[i] != ' ' && (!(str[i] >= 9 && str[i] <= 13)))
			i += 1;
		value = ft_substr(str, tmp + 1, i);
		if (setenv(var, value, 1) == -1)
			perror("setenv function failed");
	}
	free(str);
}

void	enver(t_shell *shell)
{
	char	**tab;

	if (comp("$", shell->cmd[0]))
	{
		free(shell->cmd[0]);
		shell->cmd[0] = get_var(shell, ft_substr(shell->cmd[0], 1, ft_strlen(shell->cmd[0])));
	}
	else if (comp("unset ", shell->cmd[0]))
	{
		tab = ft_split(shell->cmd[0], ' ');
		if (unsetenv(tab[1]) == -1)
			perror("unset command failed");
		free(tab);
	}
	else if (comp("export ", shell->cmd[0]))
	{
		exporter(ft_substr(shell->cmd[0], comp("export", shell->cmd[0]), ft_strlen(shell->cmd[0])));
	}
}
