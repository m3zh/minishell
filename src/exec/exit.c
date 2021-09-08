/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 10:56:49 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/08 15:04:06 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* checks if the command "exit" was put in the shell, and exits if that's */
/* the case */

void	stop(t_shell *shell)
{
	if (starts_with("exit", shell->cmd[0]) && ft_strlen(shell->cmd[0]) == 4)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}		
}
