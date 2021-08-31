/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:11:11 by mlazzare          #+#    #+#             */
/*   Updated: 2021/08/30 14:37:01 by maxdesall        ###   ########.fr       */
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

# define PATH 5
# define START 6
# define MAX 1000

struct s_signal	g_signal;

// typedef struct s_file // to refactor code
// {
// 	char	**env;
// }	        t_file;

typedef struct s_env
{
	char	**env;
}	        t_env;

typedef struct s_shell
{
	int		len;
	int		status;
	int		pipefd[2];
	pid_t	proc;
	pid_t	prev;
	int		redir;
	int		background;
	int		error_skip;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		ap; // append
	int		ow; // overwrite
	char	*infile;
	char	*outfile;
	char	*errfile;
	char	**cmd;
	char	**path;
	char	**args;
	t_env	e;
}	        t_shell;

typedef struct s_signal
{
	int	ctrl_c;
	//int	ctrl_d;
}				t_signal;

extern struct s_signal g_signal;

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
void	exec_shell(t_shell *s);
void	bash_cmd(t_shell s);
void    redir_output(t_shell *s);

/*
* ENVIRONMENT
*/ 
char	*get_var(t_shell *shell, char *str);

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
void	bash_error_unexpectedToken(t_shell *s);
void	bash_error_wFilename(t_shell *s, char *file);
int     free_arr(char **path);
int		ft_exit(t_shell *shell);
int		comp(char *s1, char *s2);


#endif
