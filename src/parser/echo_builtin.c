/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:13:39 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/16 10:21:21 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*dollar2value(t_shell *shell, char *s, int start, int size)
{
	char	*var;
	char	*var_name;

	var_name = ft_substr(s, start, size);
	if (!var_name)
		malloxit();
	var = get_var(shell, var_name);
	if (!var)
	{
		var = ft_strdup("");
		if (!var)
			malloxit();
	}
	free(var_name);
	return (var);
}

static void	get_lastRetValue(t_shell s, char **arg, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;

	j = 2;
	tmp = malloc(sizeof(char) * MAX + 1);
	if (!tmp)
		malloxit();
	l = ft_numlen(s.cmdretval);
	k = l;
	if (s.cmdretval == 0)
		tmp[0] = 0 + '0';
	while (s.cmdretval != 0 && l > 0)
	{
		tmp[--l] = s.cmdretval % 10 + '0';
		s.cmdretval /= 10;
	}
	while (arg[i][j])
		tmp[k++] = arg[i][j++];
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

void	check_echo(t_shell *s, char **arg, int i)
{
	char	*tmp;

	if (s->var.single_qts || s->var.double_qts)
		return ;
	if (!ft_strcmp(arg[0], "echo") && !ft_strncmp("$?", arg[i], 2))
		get_lastRetValue(*s, arg, i);
	else if (!ft_strcmp(arg[0], "echo")
		&& starts_with("$", arg[i]) && ft_strcmp("$", arg[i]))
	{
		tmp = dollar2value(s, arg[i], 1, sizeof(arg[i]));
		if (!tmp)
			malloxit();
		str_replace(&arg[i], tmp);
	}
}

void	check_user(t_shell *s, char **arg, int i)
{
	char	*tmp;

	if (i > 0)
		return ;
	if (starts_with("$USER", arg[i]) || !ft_strcmp("$USER", arg[i]))
	{
		tmp = dollar2value(s, arg[i], 1, sizeof(arg[i]));
		if (!tmp)
			malloxit();
		str_replace(&arg[i], tmp);
	}
}
