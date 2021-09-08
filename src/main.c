/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/08 17:37:58 by mlazzare         ###   ########.fr       */
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
	shell.cmdretval = 0;
    while (BASH)
    {
		input = readline("minishell$ ");
		ft_history(str, input);
        parse_shell(&shell, input, envp);
		exec_shell(&shell);
		// system("leaks minishell");
    }
    return (0);
}
