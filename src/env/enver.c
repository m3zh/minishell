/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:13:13 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/09 11:27:39 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* prepares the variables for the expoort function or the change_var */
/* function if the variable already exists */

static void	exporter(t_shell *shell)
{
	int		i;
	int		j;
	char	*str;
	char	*var;
	char	*value;

	j = 0;
	i = starts_with("export ", shell->cmd[0]);
	while (shell->cmd[0] && ((shell->cmd[0][i] >= 9
				&& shell->cmd[0][i] <= 13)
			|| shell->cmd[0][i] == ' '))
		i += 1;
	str = ft_substr(shell->cmd[0], i - 1, ft_strlen(shell->cmd[0]));
	while (str[j] && str[j] != '=')
		j += 1;
	var = ft_substr(str, 0, j);
	value = ft_substr(str, j + 1, ft_strlen(str));
	if (get_var(shell, var) == NULL)
		expoort(shell, str);
	else
		change_var(shell, var, value);
	free(value);
	free(var);
	free(str);
}

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
	unset(shell, str);
	free(str);
}

/* reproduces the behaviour of the "export" command */

static void	exprint(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->e.env[i])
	{
		j = 0;
		printf("declare -x ");
		while (shell->e.env[i][j] != '=')
		{
			printf("%c", shell->e.env[i][j]);
			j += 1;
		}
		printf("%s", "=\"");
		j += 1;
		while (shell->e.env[i][j])
		{
			printf("%c", shell->e.env[i][j]);
			j += 1;
		}
		printf("%c\n", '"');
		i += 1;
	}
}

/* executes environment variable commands */

static void	dollar(t_shell *shell)
{
	free(shell->cmd[0]);
	shell->cmd[0] = get_var(shell,
			ft_substr(shell->cmd[0], 1, ft_strlen(shell->cmd[0])));
}

/* redirects to the right functions */
	
void	enver(t_shell *shell)
{
	int	i;

	i = 0;
	if (starts_with("$", shell->cmd[0]))
		dollar(shell);
	else if (starts_with("env", shell->cmd[0]))
	{
		while (shell->e.env[i])
		{
			printf("%s\n", shell->e.env[i]);
			i += 1;
		}
	}
	else if (starts_with("unset ", shell->cmd[0]))
		unsetter(shell);
	else if (starts_with("export", shell->cmd[0]) && ft_strlen(shell->cmd[0]) == 6)
		exprint(shell);
	else if (starts_with("export ", shell->cmd[0]))
		exporter(shell);
	else
		return ;
	shell->builtin = 1;
}
