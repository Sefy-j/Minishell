/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:09:47 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/09 18:47:11 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

enum {
	LEFT = 49,
	RIGHT = 50,
	LEFTLEFT = 51,
	RIGHTRIGHT = 52
};

# define SPSIGN "<>|"

# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

char	**ft_argvsplit(char const *str);
char	**split_pipes(char const *str);
char	**ft_free(char **result);
int		*ft_splitcopyspecial(const char *str, char **result, int *i, int l);
char	*check_those_quotes(char *read);
void	print_matrix(char **matrix);
int		count_strs(char **arr);
t_data	*parse_machine(char **cmds, int *i);
void	ft_echo(char **args);
void	ft_pwd(char **env);
char	**ft_export(char **args, char **env);
char	**ft_unset(char **args, char **env);
void	change_shlvl(char **env);
char	**copy_matrix(char **envp);
char	**exec_builtins(t_data *head, char **env);
char	**append_str(char **origin, char *append);
void	ft_countpalspchar(const char *str, int *cpal, int *i);
void	ft_countletcom(const char *str, int *com, int *i);

#endif
