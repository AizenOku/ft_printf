/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 09:17:36 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/29 11:23:24 by ihuang           ###   ########.fr       */
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

void    ft_putstr_capitalized(char *str)
{
    while (*str)
    {
        *str = ft_toupper(*str);
        write(1, str, 1);
        str++;
    }
}

double  double_pow(double nbr, int power)
{
    double                      res;

    res = 1;
    if (power == 0)
        return (1);
    if (power == 1)
        return (nbr);
    while (power--)
        res *= nbr;
    return (res);
}

void	get_nbr_and_str_di(t_flags *flags, long long int *nbr, char **str, va_list list)
{
    if (flags->hh)
        *nbr = (char)va_arg(list, int);
    else if (flags->h)
		*nbr = (short int)va_arg(list, int);
    else if (flags->l)
	    *nbr = (long long int)va_arg(list, long int);
    else if (flags->ll)
	    *nbr = va_arg(list, long long int);
    else
		*nbr = va_arg(list, int);
    *str = (*nbr >= 0) ? ft_llitoa(*nbr) : ft_llitoa(-*nbr);
    if (!ft_strcmp(*str, "-9223372036854775808"))
    {
        free(*str);
        *str = ft_strdup("9223372036854775808");
    }
    if (*nbr == 0 && flags->prec == 0)
    {
        free(*str);
        *str = ft_strdup("");
    }
}

void	get_nbr_and_str_ouxX(t_flags *flags, char **str, va_list list)
{
    int                         base;
    unsigned long long int      nbr;
    
	if (flags->hh)
        nbr = (unsigned char)va_arg(list, unsigned int);
    else if (flags->h)
        nbr = (unsigned short)va_arg(list, unsigned int);
    else if (flags->l)
        nbr = va_arg(list, unsigned long int);
    else if (flags->ll)
        nbr = va_arg(list, unsigned long long int);
    else
        nbr = va_arg(list, unsigned int);
    if (flags->type == 5)
        base = 8;
    else if (flags->type == 6)
        base = 10;
    else if (flags->type == 7 || flags->type == 8)
        base = 16;
    else
        base = 2;
    if (flags->prec == 0 && nbr == 0 && !(flags->type == 5 && flags->hash))
        *str = ft_strdup("");
    else
        *str = ft_itoa_base_unsigned(nbr, base);
}

void	get_prepend(char *prepend, t_flags *flags, long long int nbr)
{
	*prepend = 0;
    if (flags->type > 5 && flags->type <= 8)
        return ;
    if (flags->type == 5 && flags->hash)
    {
        *prepend = '0';
        return ;
    }
	if (nbr < 0)
		*prepend = '-';
	else if (nbr >= 0 && (flags->plus || flags->space))
	{
		if (flags->space)
			*prepend = ' ';
		if (flags->plus)
			*prepend = '+';
	}
}
