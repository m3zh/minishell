/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:20:20 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/26 14:36:10 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* assistant to the exporter */

/* static void	check_nextexport(t_shell *shell, int l) */
/* { */
/* 	char	*s; */

/* 	while (shell->cmd[0][l] && ft_space(shell->cmd[0][l])) */
/* 		l++; */
/* 	if (shell->cmd[0][l] && shell->cmd[0][l + 7]) */
/* 	{ */
/* 		s = ft_substr(shell->cmd[0], l, 7); */
/* 		if (!s) */
/* 			malloxit(); */
/* 		if (!ft_strcmp(s, "export ")) */
/* 			exporter(shell, l + 7, l + 7, 0); */
/* 	} */
/* } */

/* static int	up_to_equalsign(t_shell *shell, char *str, int *i) */
/* { */
/* 	while (str[*i] && str[*i] != '=') */
/* 		*i += 1; */
/* 	if (str[*i] != '=') */
/* 		check_nextexport(shell, *i); */
/* 	return (i); */
/* } */

static int	valid_export(char *str, int i)
{
	int		start;
	char	*s;

	if (!ft_strchr(str, '='))
		return (0);
	if (!ft_isalpha(str[i]))
	{
		start = i;
		while (str[i] && (!ft_space(str[i]) && str[i] != '='))
			i++;
		s = ft_substr(str, start, i - start);
		if (!s)
			malloxit();
		printf("bash: export: \\`%s\': not a valid identifier\n", s);
		return (0);
	}
	return (1);
}

static void	assistant(t_shell *shell, char *str, char *var, int i)
{
	int		l;
	char	*newv;
	char	*value;

	l = i;
	mover(shell, str, &i);
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

void	exporter(t_shell *shell, int i, int j)
{
	char	*var;
	char	**tab;

	tab = ft_split_quotes(shell->cmd[0], ' ');
	while (!ft_strcmp(tab[j], "export"))
		j += 1;
	while (tab[j])
	{
		i = 0;
		if (valid_export(tab[j], i))
		{
			while (tab[j][i] && tab[j][i] != '=')
				i += 1;
			var = ft_substr(tab[j], 0, i);
			if (!var)
				malloxit();
			assistant(shell, tab[j], var, i);
			free(var);
		}
		j += 1;
	}
}
