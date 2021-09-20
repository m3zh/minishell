/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:49:00 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/20 11:21:45 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

pid_t	g_proc;

typedef struct s_var
{
	int	single_qts;
	int	double_qts;
}				t_var;

typedef struct s_check
{
	int	preredir;
	int	redir;
}				t_check;

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
	int		err;
	int		err_out;
	int		more;
	int		preparsing;
	int		skip_error;
	char	*stopword;
	char	*infile;
	char	*outfile;
	char	*errfile;
}				t_redir;

typedef struct s_shell
{
	int		pipelen;
	int		builtin;
	int		pipefd[2];
	int		cmdretval;
	int		envinit;
	int		cmdnotfound;
	int		error_skip;
	char	*tilde;
	char	**minienv;
	char	**cmd;
	char	**path;
	char	**args;
	t_redir	file;
	t_var	var;
	t_check	check;
}				t_shell;

#endif
