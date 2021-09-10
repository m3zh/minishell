/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/10 18:56:13 by mlazzare         ###   ########.fr       */
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

static char	*prefix(t_shell *shell)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = get_var(shell, "USER");
	if (!s1)
		return (NULL);
	s2 = ft_join("\033[1m\033[32m", s1);
	free(s1);
	s3 = ft_join(s2, "@");
	free(s2);
	s2 = ft_join(s3, "\033[0m:\033[1m\033[34m");
	free(s3);
	s1 = get_var(shell, "PWD");
	s3 = ft_join(s2, s1);
	free(s1);
	free(s2);
	s1 = ft_join(s3, "\033[0m$ ");
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
	prompt(&shell);
    rl_clear_history();
	return (0);
}
