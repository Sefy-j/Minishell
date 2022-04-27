/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:52:36 by pvillena          #+#    #+#             */
/*   Updated: 2022/02/10 20:35:48 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	*lst = NULL;
	while (temp)
	{
		free(temp);
		temp = temp->next;
	}
}
