/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/31 19:01:49 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static void write_heredoc(char **lines)
// {
//     int i;

//     i = -1;
//     while(line[++i])
//         printf("%s\n", line[i]);
//     return ;
// }

void    read_heredoc(t_shell s, char **arg)
{
    int i;
    char	*word;

    i = 0;
    word = 0;
    while (arg[i])
        i++;
    while (1)
    {
		word = readline("> ");
        if (!ft_strcmp(word, s.file.stopword))
            break ;
        if (!s.file.more)
        {
            arg[i] = ft_strdup(word);
            if (!arg[i])
            {
                free_arr(arg);
                ft_exit(&s);
            }
            i++;
        }
    }
    arg[i] = 0;
}