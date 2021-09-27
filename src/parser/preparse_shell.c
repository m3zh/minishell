/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/24 06:53:36 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_redir(t_shell *s)
{
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.infile)
		redir_input(s);
	if (s->file.outfile)
		redir_output(s);
	return (0);
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp("exit", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("cd", cmd));
}

int	not_executable(t_shell s, char *cmd)
{
	int			j;
	char		*exec;
	struct stat	sb;

	j = -1;
	if (stat(cmd, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (0);
	while (s.path[++j])
	{
		exec = ft_join(s.path[j], cmd);
		if (!exec)
			malloxit();
		if (stat(exec, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free(exec);
			return (0);
		}
		free(exec);
	}
	bash_error_cmd_not_found(&s, cmd);
	return (1);
}

int	preparse_shell(t_shell *shell, char *line)
{
	reinit_shell(shell);
	shell->cmd = ft_presplit(shell, line, '|');
	if (!shell->cmd)
		return (ft_exit(shell, "Shell cmd"));
	shell->pipelen = ft_tablen(shell->cmd);
	if (shell->error_skip)
		free_arr(shell->cmd);
	free(line);
	return (0);
}
