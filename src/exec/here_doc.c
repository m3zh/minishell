/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:08:28 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/31 17:13:43 by mlazzare         ###   ########.fr       */
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
    char	*word;

    word = 0;
    while (1)
    {
		word = readline("> ");
        if (!ft_strcmp(word, s.file.stopword))
            break ;
        write(s.file.fdin, word, ft_strlen(word));
    }
    s.file.stopword = 0;
    child_process(s, arg);
}