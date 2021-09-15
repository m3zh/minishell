/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/15 12:11:51 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	checker(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->cmd[0])
		return (0);
	while (shell->cmd[0][i]
			&& ft_space(shell->cmd[0][i]))
		i += 1;
	if (shell->cmd[0][i] == '\0')
		return (0);
	return (1);
}

void	ft_history(char *str, char *cmd)
{
	if (ft_strlen(cmd) != 0)
	{
		add_history(cmd);
		ft_strncpy(str, cmd, ft_strlen(cmd));
	}
}

static void	prompt(t_shell *shell)
{
	char	*input;
	char	str[MAX];
	
	while (BASH)
	{
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (!input)
			handle_sigusr1(SIGUSR1);
		ft_history(str, input);
		preparse_shell(shell, input);
		if (checker(shell))
			exec_shell(shell);
	}
}

int main(int ac, char **ag, char **envp)
{
	t_shell	shell;

	(void)ag;
	if (ac > 1)
		return (printf("Error\nInvalid number of arguments\n"));
	init_shell(&shell, envp);
	sheller(&shell);
	shell_signal();
	prompt(&shell);
    rl_clear_history();
	return (0);
}
