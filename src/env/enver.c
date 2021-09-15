/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesalle <mdesalle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:16:37 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 12:27:07 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* prepares the variables for the unset function */

static void	unsetter(t_shell *shell)
{
	int		i;
	char	*str;

	i = starts_with("unset ", shell->cmd[0]);
	while ((shell->cmd[0][i] >= 9 && shell->cmd[0][i] <= 13)
			|| shell->cmd[0][i] == ' ')
		i += 1;
	str = ft_substr(shell->cmd[0], i - 1, ft_strlen(shell->cmd[0]));
	if (!str)
		malloxit();
	unset(shell, str);
	free(str);
}

/* reproduces the behaviour of the "export" command */

static void	exprint(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->minienv[i])
	{
		j = 0;
		printf("declare -x ");
		while (shell->minienv[i][j] != '=')
		{
			printf("%c", shell->minienv[i][j]);
			j += 1;
		}
		printf("%s", "=\"");
		j += 1;
		while (shell->minienv[i][j])
		{
			printf("%c", shell->minienv[i][j]);
			j += 1;
		}
		printf("%c\n", '"');
		i += 1;
	}
}

/* redirects to the right functions */

void	enver(t_shell *shell)
{
	int	i;

	i = 0;
	if (starts_with("$", shell->cmd[0]) && ft_strcmp("$USER", shell->cmd[0]))
		dollar(shell);
	else if (starts_with("env", shell->cmd[0]))
	{
		while (shell->minienv[i])
		{
			printf("%s\n", shell->minienv[i]);
			i += 1;
		}
	}
	else if (starts_with("unset ", shell->cmd[0]))
		unsetter(shell);
	else if (!ft_strcmp("export", shell->cmd[0]))
		exprint(shell);
	else if (starts_with("export ", shell->cmd[0]))
		exporter(shell);
	else
		return ;
	shell->builtin = 1;
}
