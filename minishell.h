/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:09:47 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/04 20:05:40 by jlopez-f         ###   ########.fr       */
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

typedef struct s_data {
	char			**cmds;
	char			**files;
	char			*dir;
	struct s_data	*next;
}				t_data;

enum {
	LEFT = 49,
	RIGHT = 50,
	LEFTLEFT = 51,
	RIGHTRIGHT = 52
};

# define SPSIGN "<>| "

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
char	**ft_free(char **result);
int		*ft_splitcopyspecial(const char *str, char **result, int *i, int l);
char	*check_those_quotes(char *read);
t_data	*parse_machine(char **cmds);
void	print_matrix(char **matrix);

#endif
