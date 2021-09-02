/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:45:08 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/02 18:45:09 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_history(char *str, char *cmd)
{
	if (ft_strlen(cmd) != 0)
	{
		(void)str;
		add_history(cmd);
		ft_strncpy(str, cmd, ft_strlen(cmd));
		return (0);
	}
	else
		return (0);
}

int main(int ac, char **ag, char **envp)
{
	t_shell	shell;
    char	*input;
	char	str[MAX];

	if (ac > 1)
        return (printf("Error\nInvalid number of arguments\n"));
    (void)ag;
    while (BASH)
    {
		input = readline("minishell$ ");
		ft_history(str, input);
        parse_shell(&shell, input, envp);
		shell.builtin = 0;
		cd(&shell);
		enver(&shell);
		if (shell.builtin == 0)
			exec_shell(shell);
		// system("leaks minishell");
    }
    return (0);
}
