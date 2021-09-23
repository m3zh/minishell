/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:20:20 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/20 15:34:55 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*quote_creator(t_shell *shell, int *l, int start)
{
	int		i;
	char	*str;
	char	*var;

	i = 0;
	while (shell->cmd[0][*l] && shell->cmd[0][*l + 1] != '"')
		*l += 1;
	i = start;
	while (shell->cmd[0][i] && shell->cmd[0][i] != '"')
		i += 1;
	str = ft_substr(shell->cmd[0], i + 1, *l - i);
	if (!str)
		malloxit();
	var = ft_join(ft_substr(shell->cmd[0], start, i - start), str);
	if (!var)
		malloxit();
	free(str);
	shell->quotes = 1;
	*l = start;
	return (var);
}

char	*no_quotes(t_shell *shell, int l, int start)
{
	char	*str;

	str = ft_substr(shell->cmd[0], start, l - start);
	if (!str)
		malloxit();
	shell->quotes = 0;
	return (str);
}

void	mover(t_shell *shell, char *str, int *i)
{
	if (shell->quotes)
	{
		*i += 1;
		while (str[*i] && str[*i + 1] != '"')
			*i += 1;
	}
	else
	{
		while (str[*i] && !ft_space(str[*i]))
			*i += 1;
	}
}
