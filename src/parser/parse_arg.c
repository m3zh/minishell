/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:25:07 by mdesalle          #+#    #+#             */
/*   Updated: 2021/09/20 22:10:28 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_outfile(t_shell *s, char **arg, int i)
{
	int	file;

	file = i + 1;
	if (arg[file])
		swap_file(&s->file.outfile, arg, file);
	else
		return (bash_error_unexpectedToken(s, 0));
	reset_string(arg, i);
	reset_string(arg, file);
	while (arg[++file])
	{
		arg[i] = ft_strdup(arg[file]);
		if (!arg[i])
			ft_exit(s);
		i++;
	}
	arg[file] = 0;
	s->check.redir = 1;
}

static void	get_infile(t_shell *s, char **arg, int i)
{
	int	file;

	file = i + 1;
	if (arg[file] && s->file.input)
		swap_file(&s->file.infile, arg, file);
	else if (arg[file] && s->file.here_doc)
		swap_file(&s->file.stopword, arg, file);
	else
		return (bash_error_unexpectedToken(s, 0));
	reset_string(arg, i);
	reset_string(arg, file);
	if (arg[file + 1] && !ft_strcmp(arg[file + 1], "<"))
		get_infile(s, arg, file + 1);
	while (arg[++file])
	{
		s->file.more = 1;
		if (arg[i])
			free(arg[i]);
		arg[i] = ft_strdup(arg[file]);
		if (!arg[i])
			ft_exit(s);
		i++;
	}
	arg[file] = 0;
	s->check.redir = 1;
}

static void	check_redir(t_shell *s, char **arg, int i)
{
	if (s->var.single_qts || s->var.double_qts)
		return ;
	if (!ft_strcmp(arg[i], ">"))
		s->file.ow = 1;
	else if (!ft_strcmp(arg[i], ">>"))
		s->file.ap = 1;
	else if (!ft_strcmp(arg[i], "<"))
		s->file.input = 1;
	else if (!ft_strcmp(arg[i], "<<"))
		s->file.here_doc = 1;
	if ((s->file.ow || s->file.ap) && !s->file.outfile)
		get_outfile(s, arg, i);
	else if ((s->file.input && !s->file.infile)
		|| (s->file.here_doc && !s->file.stopword))
		get_infile(s, arg, i);
}

char	**parse_arg(t_shell *s, int j)
{
	int		i;
	char	**arg;

	i = -1;
	arg = ft_specialsplit(s, s->cmd[j], ' ');
	if (!arg)
		ft_exit(s);
	while (arg[++i])
	{
		check_quotes(s, arg, i);
		check_echo(s, arg, i);
		check_redir(s, arg, i);
	}
	s->var.single_qts = 0;
	return (arg);
}
