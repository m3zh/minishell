/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:13:13 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/01 16:10:58 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unsetter(t_shell *shell)
{
	int		i;
	char	*str;

	i = comp("unset ", shell->cmd[0]);
	while ((shell->cmd[0][i] >= 9 && shell->cmd[0][i] <= 13) || shell->cmd[0][i] == ' ')
		i += 1;
	str = ft_substr(shell->cmd[0], i - 1, ft_strlen(shell->cmd[0]));
	unset(str);
	free(str);
}

static void	env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i += 1;
	}
}

static void	dollar(t_shell *shell)
{
	free(shell->cmd[0]);
	shell->cmd[0] = get_var(
			ft_substr(shell->cmd[0], 1, ft_strlen(shell->cmd[0])));
}
	
void	enver(t_shell *shell)
{
	if (comp("$", shell->cmd[0]))
		dollar(shell);
	else if (comp("env", shell->cmd[0]))
		env();
	else if (comp("unset ", shell->cmd[0]))
		unsetter(shell);
	else
		return ;
	shell->builtin = 1;
}
