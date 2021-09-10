/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/10 14:20:22 by mlazzare         ###   ########.fr       */
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

int	ft_history(char *str, char *cmd)
{
	if (ft_strlen(cmd) != 0)
	{
		(void)str;
		add_history(cmd);
		ft_strncpy(str, cmd, ft_strlen(cmd));
		return (0);
	}
	return (0);
}

static void	prompt(t_shell *shell, char **envp)
{
	char	*input;
	char	str[MAX];

    while (BASH)
    {
		input = readline("minishell$ ");
		if (!input)
			handle_sigusr1(SIGUSR1);
		ft_history(str, input);
		preparse_shell(shell, input, envp);
		if (checker(shell))
			exec_shell(shell);
		// system("leaks minishell");
	}
}

int main(int ac, char **ag, char **envp)
{
	t_shell	shell;

	if (ac > 1)
		return (printf("Error\nInvalid number of arguments\n"));
	(void)ag;
	init_shell(&shell, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGQUIT, handle_sigquit);
	shell.cmdretval = 0;
	prompt(&shell, envp);
	return (0);
}
