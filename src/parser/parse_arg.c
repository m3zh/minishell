/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:59:42 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/29 10:41:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_outfile(t_shell *s, char **arg, int i, int file)
{
	if (arg[file])
		swap_file(&s->file.outfile, arg, file);
	else
		return (bash_error_unexpected_token(s, 0));
	free(arg[i]);
	arg[i] = NULL;
	free(arg[file]);
	arg[file] = NULL;
	while (arg[++file])
	{
		if (arg[i])
			free(arg[i]);
		arg[i] = ft_strdup(arg[file]);
		if (!arg[i])
			malloxit();
		i++;
	}
	arg[i] = 0;
	while (i++ < file)
		reset_string(arg, i - 1);
	return (1);
}

static int	get_infile(t_shell *s, char **arg, int i, int file)
{
	if (arg[file] && s->file.input)
		swap_file(&s->file.infile, arg, file);
	else if (arg[file] && s->file.here_doc)
		swap_file(&s->file.stopword, arg, file);
	else
		return (bash_error_unexpected_token(s, 0));
	free(arg[i]);
	arg[i] = NULL;
	free(arg[file]);
	arg[file] = NULL;
	while (arg[++file])
	{
		if (arg[i])
			free(arg[i]);
		arg[i] = ft_strdup(arg[file]);
		if (!arg[i])
			malloxit();
		i++;
	}
	arg[i] = 0;
	while (i++ < file)
		reset_string(arg, i - 1);
	return (1);
}

static int	check_redir(t_shell *s, char **arg, int i)
{
	int	redir;

	redir = 0;
	if (s->single_qts || s->double_qts)
		return (0);
	if (!ft_strcmp(arg[i], ">"))
	{
		s->file.ow = 1;
		redir = get_outfile(s, arg, i, i + 1);
	}
	else if (!ft_strcmp(arg[i], ">>"))
	{
		s->file.ap = 1;
		redir = get_outfile(s, arg, i, i + 1);
	}
	else if (!ft_strcmp(arg[i], "<"))
	{
		s->file.input = 1;
		redir = get_infile(s, arg, i, i + 1);
	}		
	else if (!ft_strcmp(arg[i], "<<"))
	{
		s->file.here_doc = 1;
		redir = get_infile(s, arg, i, i + 1);
	}
	return (redir);
}

char	**parse_arg(t_shell *s, int j)
{
	int		i;
	char	**arg;

	i = -1;
	arg = ft_specialsplit(s, s->cmd[j], ' ');
	if (!arg)
		malloxit();
	while (arg[++i])
	{
		check_quotes(s, arg, i);
		check_echo(s, arg, i);
		if (check_redir(s, arg, i))
			i--;
	}
	s->single_qts = 0;
	return (arg);
}
