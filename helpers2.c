/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:31:00 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/03 11:01:01 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_nbr_and_str_di(t_flags *flags, long long int *nbr, \
		char **str, va_list list)
{
	if (flags->hh)
		*nbr = (char)va_arg(list, int);
	else if (flags->h)
		*nbr = (short int)va_arg(list, int);
	else if (flags->l)
		*nbr = va_arg(list, long int);
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

void	get_nbr_and_str_oux(t_flags *flags, char **str, va_list list)
{
	int						base;
	unsigned long long int	nbr;

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

int		is_infinity(long double nbr)
{
	int		ret;

	ret = (nbr == 1.0 / 0.0 || nbr == -1.0 / 0.0 || nbr != nbr) ? 1 : 0;
	return (ret);
}

void	join_int_frac_strings(char **int_str, char **frac_str)
{
	char	*temp;

	temp = ft_strjoin(*int_str, ".");
	(*int_str) ? free(*int_str) : 0;
	*int_str = ft_strjoin(temp, *frac_str);
	free(temp);
	free(*frac_str);
}
