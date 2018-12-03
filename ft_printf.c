/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:38:21 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/03 10:54:18 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		call_handler(t_flags *flags, va_list list)
{
	static t_func_ptr func_list[13] = {
		&handle_c,
		&handle_s,
		&handle_p,
		&handle_d,
		&handle_d,
		&handle_o,
		&handle_u,
		&handle_x,
		&handle_bigx,
		&handle_f,
		&handle_o,
		&handle_percent,
		NULL
	};

	return (func_list[flags->type](flags, list));
}

/*
**	takes in address of fmt, and also address of flags
**	while **fmt is valid, keep increasing *fmt and fill in flags
**	as soon as you come across invalid flag/specifier,
**	break the function, don't increase *fmt
*/

int		parse_format(const char *fmt, va_list list, t_flags *flags)
{
	int			count;

	count = 0;
	while (*fmt)
	{
		while (*fmt && *fmt != '%')
			count += ft_write(fmt++);
		if (*fmt == '%')
		{
			if (*++fmt == '\0')
				return (count);
			get_flags(&fmt, flags);
			if (flags->type != -1)
				count += call_handler(flags, list);
			initiate_flags(&flags);
		}
	}
	free(flags);
	return (count);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		list;
	int			res;
	t_flags		*flags;

	flags = NULL;
	va_start(list, format);
	initiate_flags(&flags);
	res = parse_format(format, list, flags);
	va_end(list);
	return (res);
}
