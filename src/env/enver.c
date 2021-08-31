/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:13:13 by maxdesall         #+#    #+#             */
/*   Updated: 2021/08/31 11:46:01 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
}
