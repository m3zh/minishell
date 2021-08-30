/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:07:58 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/30 10:54:57 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char **get_env(t_shell *s, char **env)
{
	int i;
	char **tab;

	i = -1;
	tab = malloc(sizeof(char *) * MAX + 1);
	if (!tab)
		ft_exit(s);
	while (env[++i])
	{
		tab[i] = ft_strdup(env[i]);
		if (!tab[i])
			ft_exit(s);
	}
	tab[i] = 0;
	return (tab);
}

static char	**get_paths(char **ep)
{
	char	**ret;
	char	*env;
	int		i;

	i = -1;
	while (ep[++i])
	{
		if (!ft_strncmp(ep[i], "PATH=", PATH))
		{
			env = ft_substr(ep[i], START, ft_strlen(ep[i]));
			if (!env)
				exit(EXIT_FAILURE);
			ret = ft_splitpath(env, ':');
			if (!ret)
			{
				free(env);
				exit(EXIT_FAILURE);
			}
			free (env);
			return (ret);
		}
	}
	return (NULL);
}

void	init_shell(t_shell *s, char **envp)
{
	s->len = 0;
	s->status = 0;
	s->infile = 0;
	s->outfile = 0;
	s->errfile = 0;
	s->background = 0;
	s->redir = 0;
	// s->error_skip = 0;
	s->proc = 0;
	s->prev = 0;
	s->tmpin = 0;
	s->tmpout = 0;
	s->fdin = 0;
	s->fdout = 0;
	s->ow = 0;
	s->ap = 0;
	s->fi = 0;
	s->here_doc = 0;
    s->path = get_paths(envp);
	if (!s->path)
		ft_exit(s);
	s->e.env = get_env(s, envp); // this parsing will have to be redone in a more accurate way
	if (!s->e.env)			
		ft_exit(s);
	s->cmd = 0;
	s->args = 0;
}
    