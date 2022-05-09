/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:29:26 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/09 18:31:23 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lenchar(char const *s, int c)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] != c && s[len])
		len++;
	return (len);
}