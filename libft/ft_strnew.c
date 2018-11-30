/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:07:52 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/21 11:27:49 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	char	*start;

	start = NULL;
	if ((s = malloc(sizeof(char) * (size + 1))) != NULL)
	{
		start = s;
		while (size--)
			*s++ = '\0';
		*++s = '\0';
		s = start;
	}
	return (s);
}
