/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:57:34 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/15 11:01:02 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strindex (const char *s, const char c)
** returns the index position of the char in the str
** e.g. ft_strindex("abc", 'c') would return 2
** if const char c is not found in const char *s
** ft_strindex returns -1
*/

int		ft_strindex(const char *s, const char c)
{
	int		i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}
