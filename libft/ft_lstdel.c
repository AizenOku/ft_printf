/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:17:24 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/15 18:32:11 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	temp = NULL;
	if (!alst)
		return ;
	while (*alst)
	{
		temp = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = temp;
	}
	alst = NULL;
}
