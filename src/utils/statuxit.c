/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 09:28:31 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/09 11:26:51 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	statuxit(t_shell *shell, int status)
{
	if (status >= 0 && status <= 255)
		exit(status);
	else if (status < 0)
	{
		while (status < 0)
			status += 256;
		exit(status);
	}
	else if (status > 255)
	{
		while (status > 255)
			status -= 256;
		exit(status);
	}
	else
		exit(EXIT_FAILURE);
}
