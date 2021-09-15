/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:20:20 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/15 14:11:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* assistant to the exporter */

static void	assistant(t_shell *shell, char *str, char *var, int i)
{
	int 	l;
	char	*newv;
	char	*value;

	l = i;
	while (str[i] && !ft_space(str[i]))
		i++;
	value = ft_substr(str, l + 1, i - l);
	if (!value)
		malloxit();
	newv = get_var(shell, var);
	if (newv == NULL)
		expoort(shell, str);
	else
	{
		if (!change_var(shell, var, value))
			exit(EXIT_FAILURE);
	}
	free(newv);
	free(value);
}

/* prepares the variables for the expoort function or the change_var */
/* function if the variable already exists */

void	exporter(t_shell *shell, int l)
{
	int		i;
	int		start;
	char	*str;
	char	*var;
	char	*s;

	while (shell->cmd[0][l] && ft_space(shell->cmd[0][l]))
		l += 1;
	start = l;
	while (shell->cmd[0][l] && !ft_space(shell->cmd[0][l]))
		l += 1;
	str = ft_substr(shell->cmd[0], start, l - start);
	printf("str %s\n", str);
	if (!str)
		malloxit();
	i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	if (!str[i] || str[i] != '=')
	{
		free(str);
		return ;
	}
	var = ft_substr(str, 0, i);
	if (!var)
		malloxit();
	assistant(shell, str, var, i);
	free(var);
	free(str);
	while (shell->cmd[0][l] && ft_space(shell->cmd[0][l]))
		l++;
	if (shell->cmd[0][l] && shell->cmd[0][l + 7])
	{
		s = ft_substr(shell->cmd[0], l, 7);
		if (!s)
			malloxit();
		if (!ft_strcmp(s, "export "))
			exporter(shell, l + 7);
		free(s);
	}
}
