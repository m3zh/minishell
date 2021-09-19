/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:45:52 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/19 16:30:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  is_dollar(char *s, int i)
{
	return ((i == 0 && s[i] == DOLLARSIGN)
			|| (i > 0 && s[i] == DOLLARSIGN && s[i - 1] != BACKSLASH));
}

static char	*overwrite_dollarvalue(t_shell *s, char *str, int *j)
{
    int     start;
	char	*value;
    char    *var;

	start = *j;
	while (str[*j] && ft_isalnum(str[*j]))
		(*j)++;
	value = ft_substr(str, start, *j - start);
	if (!value)
		malloxit();
	var = get_var(s, value);
	if (!var)
		malloxit();
	ft_free(value);
    return (var);
}

static void doubleqts_stringify(t_shell *s, char **arg, int i)
{
	int     j;
	int     k;
	char    *tmp;
	char    *var;

	k = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (MAX + 1));
	if (!tmp)
		malloxit();
	while (arg[i][++j])
	{
		if (is_dollar(arg[i], j))
		{
			j++;
			var = overwrite_dollarvalue(s, arg[i], &j);
			if (var)
				k = ft_strlcat(tmp, var, MAX + 1);
			ft_free(var);
			j--;
		}
		else if (valid_dbquote(arg[i], j, DOUBLEQTS))
			tmp[k++] = arg[i][j];
	}
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
	s->var.double_qts = 0;
}

/*
*  This function removes single quotes from the string
*/

static void singleqts_stringify(char **arg, int i)
{
	int     j;
	int     k;
	char    *tmp;

	j = -1;
	k = 0;
	
	tmp = malloc(sizeof(char) * (MAX + 1));
	if (!tmp)
		malloxit();
	while (arg[i][j])
		if (arg[i][j] != SINGLEQTS)
			tmp[k++] = arg[i][j];
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

void check_quotes(t_shell *s, char **arg, int i)
{
	if (starts_with("\'", arg[i]))
		s->var.single_qts = 1;
	else if (starts_with("\"", arg[i]))
		s->var.double_qts = 1;       
	if (s->var.single_qts)
		singleqts_stringify(arg, i);
	else if (s->var.double_qts)
		doubleqts_stringify(s, arg, i);
}