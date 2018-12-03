/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 09:17:36 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/02 19:45:17 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_write(const char *fmt)
{
	write(1, fmt, 1);
	return (1);
}

void	write_padding(int spaces, char c)
{
	while (spaces-- > 0)
		write(1, &c, 1);
}

void	check_stars(t_flags *flags, va_list list)
{
	if (flags->star_width)
		flags->width = va_arg(list, int);
	if (flags->width < 0)
		flags->width = -(flags->width);
	if (flags->star_prec)
		flags->prec = va_arg(list, int);
}

void	ft_putstr_capitalized(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		write(1, str, 1);
		str++;
	}
}

double	double_pow(double nbr, int power)
{
	double	res;

	res = 1;
	if (power == 0)
		return (1);
	if (power == 1)
		return (nbr);
	while (power--)
		res *= nbr;
	return (res);
}
