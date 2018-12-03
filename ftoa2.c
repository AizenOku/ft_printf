/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:25:57 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/03 10:05:10 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	get_doublenbr(t_flags *flags, va_list list)
{
	long double	nbr;

	if (flags->bigl)
		nbr = va_arg(list, long double);
	else
		nbr = va_arg(list, double);
	return (nbr);
}

void		get_prepend_double(char **int_str, char *prepend, t_flags *flags)
{
	char		*temp;

	*prepend = 0;
	temp = NULL;
	if (**int_str == '-' && !ft_strstr(*int_str, "-inf"))
	{
		*prepend = '-';
		temp = ft_strdup(*int_str + 1);
		free(*int_str);
		*int_str = temp;
	}
	else if (flags->plus || flags->space)
	{
		if (flags->space)
			*prepend = ' ';
		if (flags->plus)
			*prepend = '+';
	}
}

int			tie_to_even(char **int_str, char **frac_str)
{
	int			dig_places;
	int			int_places;
	int			is_odd;

	dig_places = ft_strlen(*frac_str);
	int_places = 0;
	is_odd = 0;
	if (dig_places > 0)
	{
		is_odd = ((*(*frac_str + dig_places - 1) - '0') % 2 == 1);
		if (is_odd)
			increment_str(frac_str, 'f');
	}
	if (dig_places == 0)
	{
		int_places = ft_strlen(*int_str);
		is_odd = ((*(*int_str + int_places - 1) - '0') % 2 == 1);
		if (is_odd)
			increment_str(int_str, 'i');
	}
	return (0);
}

int			increment_str(char **str, char type)
{
	char		*p;
	char		*temp;
	int			count;

	count = ft_strlen(*str);
	p = *str + count - 1;
	while (count-- && *p != '-')
	{
		if (*p - '0' + 1 < 10)
		{
			*p += 1;
			break ;
		}
		*p = (*p - '0' + 1) % 10 + '0';
		p--;
	}
	if (type == 'i' && (*p == '-' || count == -1))
	{
		temp = *p == '-' ? ft_strjoin("-1", *str + 1) : ft_strjoin("1", *str);
		free(*str);
		*str = temp;
	}
	else if (type == 'f' && count == -1)
		return (1);
	return (0);
}

double		set_infinity(long double nbr, char **int_str)
{
	if (nbr == 1.0 / 0.0)
		*int_str = ft_strdup("inf");
	else if (nbr == -1.0 / 0.0)
		*int_str = ft_strdup("-inf");
	else
		*int_str = ft_strdup("nan");
	return (1.0 / 0.0);
}
