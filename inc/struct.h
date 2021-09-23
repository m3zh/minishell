/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:49:00 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/22 15:44:57 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

pid_t	g_proc;

typedef struct s_redir
{
	int		tmpin;
	int		tmpout;
	int		tmpfd;
	int		fdin;
	int		fdout;
	int		ap;
	int		ow;
	int		input;
	int		here_doc;
	int		more;
	char	*stopword;
	char	*infile;
	char	*outfile;
}				t_redir;

typedef struct s_shell
{
	int		pipelen;
	int		builtin;
	int		pipefd[2];
	int		single_qts;
	int		double_qts;
	int		cmdretval;
	int		cmdnotfound;
	int		error_skip;
	int		quotes;
	int		no_path;
	char	*tilde;
	char	**minienv;
	char	**cmd;
	char	**path;
	char	**arg;
	t_redir	file;
}				t_shell;

#endif
