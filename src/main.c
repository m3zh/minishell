/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/13 11:38:56 by mlazzare         ###   ########.fr       */
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

static char	*prefix(t_shell *shell)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = get_var(shell, "USER");
	s2 = ft_join("\033[1m\033[32m", s1);
	if (!s2)
		malloxit();
	free(s1);
	s3 = ft_join(s2, "@\033[0m:\033[1m\033[34m");
	free(s2);
	s1 = get_var(shell, "PWD");
	s2 = ft_join(s3, s1);
	if (!s2)
		malloxit();
	free(s1);
	s1 = ft_join(s2, "\033[0m$ ");
	if (!s1)
		malloxit();
	free(s2);
	free(s3);
	return (s1);
}
	
static void	prompt(t_shell *shell)
{
	char	*input;
	char	str[MAX];
	char	*tmp;
	
	while (BASH)
	{
		tmp = prefix(shell);
		input = readline(tmp);
		free(tmp);
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
	shell_signal();
	prompt(&shell);
    rl_clear_history();
	return (0);
}
