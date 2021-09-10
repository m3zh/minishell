/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 10:56:49 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/10 18:59:40 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* checks if the command "exit" was put in the shell, and exits if that's */
/* the case */

void	stop(t_shell *shell)
{
	char **cmd;

	if (!starts_with("exit", shell->cmd[0]))
		return ;
	if (!ft_strcmp("exit", shell->cmd[0]))
	{
		printf("exit\n");
		ft_exit(shell);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	cmd = ft_split(shell->cmd[0], ' ');
	if (!cmd)
		malloxit();
	if (ft_tablen(cmd) == 2)
	{
		if (ft_isword(cmd[1]))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", cmd[1]);
			ft_exit(shell);
		}
		else
		{
			printf("exit\n");
			ft_exit(shell);
		}
	}
	else if (ft_tablen(cmd) > 2)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		shell->builtin = 1;
	}	
}
