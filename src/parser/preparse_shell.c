/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:53 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/16 15:47:52 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	preparse_shell(t_shell *shell, char *line)
{
	reinit_shell(shell);
	shell->cmd = ft_presplit(line, '|');
	if (!shell->cmd)
		return (ft_exit(shell));
	shell->pipelen = ft_tablen(shell->cmd);
	free(line);
	return (0);
}
