/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:23:34 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/19 17:33:16 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_d(t_flags *flags, va_list list)
{
	char			*str;
	long long int	nbr;
	int				spaces;
	char			prepend;
	int				slen;

	check_stars(flags, list);
	get_nbr_and_str_di(flags, &nbr, &str, list);
	slen = (int)ft_strlen(str);
	get_prepend(&prepend, flags, nbr);
	spaces = flags->width - MAX(flags->prec, slen) - (prepend != 0);
	if (!flags->minus && !(flags->prec == -1 && flags->zero))
		write_padding(spaces, ' ');
	if (prepend)
		write(1, &prepend, 1);
	if (flags->prec == -1 && flags->zero && !flags->minus)
		write_padding(spaces, '0');
	else if (flags->prec - slen > 0)
		write_padding(flags->prec - slen, '0');
	ft_putstr(str);
	if (flags->minus)
		write_padding(spaces, ' ');
	free(str);
	return (MAX(flags->width, MAX(flags->prec, slen) + (prepend != 0)));
}

int		handle_o(t_flags *flags, va_list list)
{
	char			*str;
	char			prepend;
	int				spaces;
	int				slen;
	int				plen;

	check_stars(flags, list);
	get_nbr_and_str_ouxX(flags, &str, list);
	slen = (int)ft_strlen(str);
	get_prepend(&prepend, flags, 0);
	plen = (prepend && *str && *str != '0') ? 1 : 0;
	spaces = flags->width - MAX(flags->prec, slen) - plen;
	if (!flags->minus && !(flags->prec == -1 && flags->zero))
		write_padding(spaces, ' ');
	if (prepend && (*str != '0' && *str))
		write(1, &prepend, 1);
	if (flags->prec == -1 && flags->zero && !flags->minus)
		write_padding(spaces, '0');
	else if (flags->prec - slen - plen> 0)
		write_padding(flags->prec - slen - plen, '0');
	ft_putstr(str);
	if (flags->minus)
		write_padding(spaces, ' ');
	free(str);
	return (MAX(flags->width, MAX(flags->prec, slen) + plen));
}

int		handle_u(t_flags *flags, va_list list)
{
	char			*str;
	int				slen;
	char			prepend;
	int				spaces;

	check_stars(flags, list);
	get_nbr_and_str_ouxX(flags, &str, list);
	slen = (int)ft_strlen(str);
	get_prepend(&prepend, flags, 0);
	spaces = flags->width - MAX(flags->prec, slen) - (prepend != 0);
	if (!flags->minus && !(flags->zero && flags->prec == -1))
		write_padding(spaces, ' ');
	if (prepend)
		write(1, &prepend, 1);
	if (flags->prec == -1 && flags->zero)
		write_padding(spaces, '0');
	else if (flags->prec - slen > 0)
		write_padding(flags->prec - slen, '0');
	ft_putstr(str);
	if (flags->minus)
		write_padding(spaces, ' ');
	free(str);
	return (MAX(flags->width, MAX(flags->prec, slen) + (prepend != 0)));
}

int		handle_x(t_flags *flags, va_list list)
{
	char			*str;
	char			*prepend;
	int				slen;
	int				plen;
	int				spaces;

	check_stars(flags, list);
	get_nbr_and_str_ouxX(flags, &str, list);
	prepend = (flags->hash) ? ft_strdup("0x") : NULL;
	plen = (prepend && *str && *str != '0') ? 2 : 0;
	slen = ft_strlen(str);
	spaces = flags->width - MAX(flags->prec, slen) - plen;
	if (!flags->minus && !(flags->zero && flags->prec == -1))
		write_padding(spaces, ' ');
	(prepend && (*str != '0' && *str)) ? write(1, prepend, 2) : 0;
	if (flags->prec == -1 && flags->zero && !flags->minus)
		write_padding(spaces, '0');
	else if (flags->prec - slen > 0)
		write_padding(flags->prec - slen, '0');
	ft_putstr(str);
	flags->minus ? write_padding(spaces, ' ') : 0;
	free(str);
	prepend ? free(prepend) : 0;
	return (MAX(flags->width, MAX(flags->prec, slen) + plen));
}

int		handle_X(t_flags *flags, va_list list)
{
	char			*str;
	char			*prepend;
	int				slen;
	int				plen;
	int				spaces;

	check_stars(flags, list);
	get_nbr_and_str_ouxX(flags, &str, list);
	prepend = (flags->hash) ? ft_strdup("0X") : NULL;
	plen = (prepend && *str) ? 2 : 0;
	slen = ft_strlen(str);
	spaces = flags->width - MAX(flags->prec, slen) - plen;
	if (!flags->minus && !(flags->zero && flags->prec == -1))
		write_padding(spaces, ' ');
	(prepend && (*str != '0' && *str)) ? write(1, prepend, 2) : 0;
	if (flags->prec == -1 && flags->zero && !flags->minus)
		write_padding(spaces, '0');
	else if (flags->prec - slen > 01)
		write_padding(flags->prec - slen, '0');
	ft_putstr_capitalized(str);
	(flags->minus) ? write_padding(spaces, ' ') : 0;
	free(str);
	prepend ? free(prepend) : 0;
	return (MAX(flags->width, MAX(flags->prec, slen) + plen));
}