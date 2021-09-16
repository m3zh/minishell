/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:45:12 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/16 14:16:26 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	starts_with(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i += 1;
	if (s1[i] == '\0')
		return (i + 1);
	return (0);
}

void	str_replace(char **dst, char *src)
{
	if (!src)
		return ;
	if (*dst)
		free(*dst);
	*dst = ft_strdup(src);
	if (!*dst)
		malloxit();
	free(src);
}

void	swap_file(char **file, char **arg, int i)
{
	if (*file)
		free(*file);
	*file = ft_strdup(arg[i]);
	if (!*file)
		malloxit();
}
