/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:07:58 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/01 17:04:38 by maxdesall        ###   ########.fr       */
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

static void init_fileredir(t_shell *s)
{
	s->file.tmpin = 0;
	s->file.tmpout = 0;
	s->file.tmpfd = 0;
	s->file.fdin = 0;
	s->file.fdout = 0;
	s->file.ow = 0;
	s->file.ap = 0;
	s->file.input = 0;
	s->file.here_doc = 0;
	s->file.stopword = 0;
	s->file.more = 0;
	s->file.infile = 0;
	s->file.outfile = 0;
	s->file.errfile = 0;
}

static void	envinit(void)
{
	int		i;
	char	**tmp;

	i = 0;
	while (environ[i])
		i += 1;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return ;
	i = 0;
	while (environ[i])
	{
		tmp[i] = malloc(sizeof(char) * (ft_strlen(environ[i]) + 1));
		if (!tmp[i])
			return ;
		ft_strlcpy(tmp[i], environ[i], ft_strlen(environ[i]) + 1);
		i += 1;
	}
	tmp[i] = 0;
	environ = tmp;
}

void	init_shell(t_shell *s, char **envp)
{
	envinit();
	init_fileredir(s);
	s->len = 0;
	s->status = -1;
	s->background = 0;
	// s->error_skip = 0;
    s->path = get_paths(envp);
	if (!s->path)
		ft_exit(s);
	s->e.env = get_env(s, envp); // this parsing will have to be redone in a more accurate way
	if (!s->e.env)			
		ft_exit(s);
	s->cmd = 0;
	s->args = 0;
}
    
