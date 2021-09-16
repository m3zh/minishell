/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 10:56:49 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/16 10:38:11 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	tabtwo(t_shell *shell, char **cmd)
{
	(void)shell;
	if (ft_isword(cmd[1]))
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", cmd[1]);
		exit(2);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
}

/* checks if the command "exit" was put in the s, and exits if that's */
/* the case */

void	stop(t_shell *s)
{
	char	**cmd;

	if (!starts_with("exit", s->cmd[0]))
		return ;
	if (!ft_strcmp("exit", s->cmd[0]))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	cmd = ft_split(s->cmd[0], ' ');
	if (!cmd)
		malloxit();
	if (ft_tablen(cmd) == 2)
		tabtwo(s, cmd);
	else if (ft_tablen(cmd) > 2)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		s->cmdretval = errno;
		free_arr(cmd);
		s->builtin = 1;
	}	
}
