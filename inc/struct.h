/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:38:45 by mlazzare          #+#    #+#             */
/*   Updated: 2021/09/07 09:31:41 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

extern char	**environ;

typedef struct s_env
{
	char	**env;
}	        t_env;

typedef struct s_var 
{
	int	single_qts;
	int double_qts;
} t_var;

typedef struct s_check 
{
	int	preredir;
	int redir;
} t_check;

typedef struct s_redir
{
	int		tmpin;
	int		tmpout;
	int		tmpfd;
	int		fdin;
	int		fdout;
	int		ap; // append >>
	int		ow; // overwrite >
	int		input; // file input <
	int		here_doc; // <<
	int		lastErr;
	int		allErr;
	int		more; // check if there is more after <,<<,>>,>
	int		preparsing;
	char	*stopword;
	char	*infile;
	char	*outfile;
	char	*errfile;
}	        t_redir;

typedef struct s_shell
{
	int		pipelen;
	int		builtin;
	int		status;
	int		pipefd[2];
	int		background;
	int		error_skip;
	char	*tilde;
	char	**cmd;
	char	**path;
	char	**args;
	pid_t	proc;
	t_env	e;
	t_redir	file;
	t_var	var;
	t_check	check;
}	        t_shell;

typedef struct s_signal
{
	int	ctrl_c;
	//int	ctrl_d;
}				t_signal;

#endif
