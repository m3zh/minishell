/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:35:57 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/08 15:25:27 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	malloxit(void)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR);
	exit(EXIT_FAILURE);
}
