/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:20:27 by maxdesall         #+#    #+#             */
/*   Updated: 2021/09/01 07:38:45 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BASH 1
# define PATH 5
# define START 6
# define MAX 1000

# define TMPFILE "tmpfile"

typedef struct s_env
{
	char	**env;
}	        t_env;

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
	int		more;
	char	*stopword;
	char	*infile;
	char	*outfile;
	char	*errfile;
}	        t_redir;

typedef struct s_shell
{
	int		len;
	int		status;
	int		pipefd[2];
	int		background;
	int		error_skip;
	char	**cmd;
	char	**path;
	char	**args;
	pid_t	proc;
	t_env	e;
	t_redir	file;
}	        t_shell;

typedef struct s_signal
{
	int	ctrl_c;
	//int	ctrl_d;
}				t_signal;


/*
* PARSING
*/

void	init_shell(t_shell *s, char **envp);
int		parse_shell(t_shell *shell, char *line, char **envp);
char	**parse_arg(t_shell *s, int i);


/*
* EXECUTION
*/

int     check_cmd(t_shell *s);
int		cd(t_shell *shell);
void	bash_cmd(t_shell s);
void	exec_shell(t_shell *s);
void    redir_input(t_shell *s);
void    redir_output(t_shell *s);
void    redir_heredoc(t_shell *s);
void    read_heredoc(t_shell *s, char **arg, int i);
void	child_process(t_shell s, char **arg, int i);

/*
* ENVIRONMENT
*/ 
char	*get_var(t_shell *shell, char *str);
void	enver(t_shell *shell);

/*
* SIGNALS
*/

void	which_signal();

/*
* UTILS
*/

void	reset_string(char **s, int i);
void    reset_shell(t_shell *s);
void	free_struct(t_shell *s);
void	ft_free(char *s);
void	bash_error_unexpectedToken(t_shell *s);
void	bash_error_wFilename(t_shell *s, char *file);
int     free_arr(char **path);
int		ft_exit(t_shell *shell);
int		comp(char *s1, char *s2);


#endif
