/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 07:35:18 by maxdesall         #+#    #+#             */
/*   Updated: 2021/08/31 09:13:15 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* goes to a specific directory, example: "cd some-directory" */

static void	folder(char *cmd)
{
	char	*tmp;
	char	*pwd;
	char	*nstr;

	pwd = getcwd(NULL, 0);
	nstr = ft_join(pwd, "/");
	tmp = nstr;
	nstr = ft_join(tmp, cmd);
	free(tmp);
	if (!chdir(cmd))
		setenv("PWD", nstr, 1);
	else
		perror("cd command failed");
}

/* goes to a specific directory when using the tilde */
/* example: "cd ~/some-directory" */

static void	tilde(char *cmd, char *str)
{
	char	*nstr;

	nstr = ft_join(str, ft_substr(cmd, 1, ft_strlen(cmd)));
	if (!chdir(nstr))
		setenv("PWD", nstr, 1);
	else
		perror("cd command failed");
}

/* goes back to the home folder, example: "cd" */

static void	homer(char *str)
{
	if (!chdir(str))
		setenv("PWD", str, 1);
	else
		perror("cd command failed");
}

/* redirects to the right functions */

static void	redirect(char *cmd, char *option, char *home)
{
	if (comp("cd", cmd))
	{
		if (!option)
			homer(home);
		else
		{
			if (comp("~/", option))
				tilde(option, home);
			else
				folder(option);
		}
	}
}

/* assigns the right values to the newly created variables */
/* calls the redirection function and frees everything */

int	cd(t_shell *shell)
{
	char	*str;
	char	**tab;
	
	str = get_var(shell, "HOME");
	tab = ft_split(shell->cmd[0], ' ');
	redirect(tab[0], tab[1], str);
	free(str);
	free(tab);
	return (0);
}
