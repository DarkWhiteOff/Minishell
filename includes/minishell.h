/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:25 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/19 16:46:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define _X_OPEN_SOURCE 700 faudra m'expliquer à quoi ça sert juste

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define GREY 	"\033[0;90m"
# define RESET	"\033[0m"

enum e_type {command, argument, sc, end};

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

typedef struct s_main {
    char	**env;
    int		env_len;
    char	**export;
    int		export_len;
    t_token	*tokens;
    int		tokens_len;
    int     split_len;
    int		nb_cmd;
    char	*path;
}	t_main;


// LIBFT
size_t	ft_atoi(const char *str);
int		ft_isspace(int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int	    ft_isdigit(int c);

// MINISHELL
/// Env
int		init_env(char **env, t_main *main);
int     check_syntax_env(t_main *main, char **split);
void	print_env(t_main *main, int check, char **split);
/// Unset
void	unset(t_main *main, char *cmd);
int		check_syntax_unset(char *cmd);
void	prep_unset(t_main *main, char **split);
/// Export
void	export(t_main *main, char *cmd);
int		check_syntax_export(char *cmd);
void	fill_export(t_main *main, char *cmd);
void	fill_env_export(t_main *main, char *cmd);
void	prep_export(t_main *main, char **split);
void	print_ascii_order(t_main *main);
void	prep_export(t_main *main, char **split);
char	*get_var_name(char *cmd);
/// Echo
void	ft_echo(char **cmd);
int		get_fd(char **cmd);
// Cd
void	update_oldpwd_pwd(t_main *main);
int		cd(t_main *main, char **cmd);
// Pwd
int		pwd(t_main *main, char **cmd);
/// Utils BuiltIns
int		check_var_exists(char **env, int len, char *cmd);
void	remake_env(char	**tmp, char	**env, int env_len, int replace_pos);
//Utils
int		only_space_line(char *cmd);
int     get_cmd_number(t_main *main, char **split);
char	**ft_split_k_q_s(t_main *main, char const *s, char c);
int	closed_quotes(const char *s);	
char        *get_rid_of_spaces(char const *s);
char        *cut_str(char *str, char *cut);

/// Tokens
int		init_tokens(char **split, t_main *main);
int		is_cmd(char *s, char *path);
int		is_sc(char *s);
int		ft_findmltpchar(char *s1, char *s2);
int		check_builtin(char *s);
char	*get_rid_of_quotes(char *s);
char        *get_rid_of(char *s, char c);

/// Utils Tokens
int		ft_quote(char **s, char **split);
char	**clean_split(t_main *main, char **split);
int	    handle_sc(t_main *main, char **split, int i);
//EXEC
int	ft_exec(t_main *main, char **split, char *cmd);
//PIPEX
void    prep_cmd_pipex(t_main *main, char **split);
void        pipex(t_main *main, char *split_pipex);

// FREE
void	free_all_data(t_main *main);
void	free_env(char **tab, int tablen);
void	free_tokens(t_main *main);
void    free_end_cmd(t_main *main, char **split);
void    free_split(char **split);


char	*ft_strendchr(char *s, char end);
int	    check_var_exists2(t_main *main, char *arg);
char	*ft_strchrb(const char *s, int c);
#endif