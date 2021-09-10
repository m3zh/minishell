/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 07:35:18 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/10 19:13:35 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* goes to a specific directory, example: "cd some-directory" */

static void	folder(t_shell *shell, char *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(cmd))
	{
		change_var(shell, "OLDPWD", pwd);
		pwd = getcwd(NULL, 0);
		change_var(shell, "PWD", pwd);
		free(pwd);
	}
	else
	{
		free(pwd);
		printf("bash: cd: %s: %s\n", cmd, strerror(errno));
	}
}

/* goes to a specific directory when using the tilde */
/* example: "cd ~/some-directory" */

static void	tilde(t_shell *shell, char *cmd, char *str)
{
	char	*pwd;
	char	*tmp;
	char	*nstr;

	pwd = getcwd(NULL, 0);
	tmp = ft_substr(cmd, 1, ft_strlen(cmd));
	if (!tmp)
		malloxit();
	nstr = ft_join(str, tmp);
	if (!nstr)
		malloxit();
	if (shell->tilde)
		free(shell->tilde);
	shell->tilde = cmd;
	if (!chdir(nstr))
	{
		change_var(shell, "OLDPWD", pwd);
		pwd = getcwd(NULL, 0);
		change_var(shell, "PWD", pwd);
	}
	else
		perror("cd command failed");
}

/* goes back to the home folder, example: "cd" */

static void	homer(t_shell *shell, char *str)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(str))
	{
		change_var(shell, "OLDPWD", pwd);
		pwd = getcwd(NULL, 0);
		change_var(shell, "PWD", pwd);
	}
	else
		perror("cd command failed");
}

/* redirects to the right functions */

static void	redirect(t_shell *shell, char *cmd, char *option, char *home)
{
	if (starts_with("cd", cmd) && ft_strlen(cmd) == 2)
	{
		if (!option)
			homer(shell, home);
		else
		{
			if (starts_with("~/", option))
				tilde(shell, option, home);
			else if (starts_with("-", option) && ft_strlen(option) == 1)
				tilde(shell, shell->tilde, home);
			else
				folder(shell, option);
		}
		shell->builtin = 1;
	}
}

/* assigns the right values to the newly created variables */
/* calls the redirection function and frees everything */

void	cd(t_shell *shell)
{
	char	*str;
	char	**tab;
	
	if (shell->pipelen > 1)
		return ;
	str = get_var(shell, "HOME");
	tab = ft_split(shell->cmd[0], ' ');
	if (!tab)
		malloxit();
	redirect(shell, tab[0], tab[1], str);
	free(str);
	free_arr(tab);
}
