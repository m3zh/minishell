/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:43:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/08 11:52:44 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	checker(t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	if (!shell->cmd[0])
// 		return (0);
// 	while (shell->cmd[0][i] && ((shell->cmd[0][i] >= 9 && shell->cmd[0][i] <= 13) || shell->cmd[0][i] == ' '))
// 		i += 1;
// 	if (shell->cmd[0][i] == '\0')
// 		return (0);
// 	return (1);
// }

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
		exec_shell(shell);
		// system("leaks minishell");
    }
    return (0);
}
