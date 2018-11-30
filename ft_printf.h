/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:41:44 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/29 23:09:41 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# define SET_IF(condition, x) if (condition) x = 1;
# define MAX(a, b) ((a > b) ? a : b)
# define MIN(a, b) ((a < b) ? a : b)

typedef struct	s_flags
{
	char		minus;
	char		plus;
	char		space;
	char		zero;
	char		hash;
	char		star_width;
	int			width;
	char		star_prec;
	int			prec;
	char		ll;
	char		l;
	char		hh;
	char		h;
	char		L;
	int			type;
}				t_flags;

typedef int 	(*func_ptr)(t_flags *flags, va_list list);

void			get_nbr_and_str_di(t_flags *flags, \
long long int *nbr, char **str, va_list list);
void			get_nbr_and_str_ouxX(t_flags *flags, char **str, va_list list);
void			get_prepend(char *prepend, t_flags *flags, long long int nbr);
void			get_prepend_double(char **int_str, char *prepend, t_flags *flags);

int				call_handler(t_flags *flags, va_list list);
int				handle_s(t_flags *flags, va_list list);
int				handle_c(t_flags *flags, va_list list);
int				handle_p(t_flags *flags, va_list list);
int				handle_d(t_flags *flags, va_list list);
int				handle_o(t_flags *flags, va_list list);
int				handle_u(t_flags *flags, va_list list);
int				handle_x(t_flags *flags, va_list list);
int				handle_X(t_flags *flags, va_list list);
int				handle_f(t_flags *flags, va_list list);
int				handle_percent(t_flags *flags, va_list list);

void			initiate_flags(t_flags **flags);
void			get_flags(const char **fmt, t_flags *flags);
void			set_len(const char **fmt, t_flags *flags);
void			set_flag(const char **fmt, t_flags *flags);
void			set_width_and_prec(const char **fmt, t_flags *flags);

int				ft_printf(const char *restrict format, ...);
int				parse_format(const char *fmt, va_list list, t_flags *flags);
void			print_flags(t_flags *flags);

int				ft_write(const char *fmt);
void			write_padding(int spaces, char c);
void			check_stars(t_flags *flags, va_list list);
void			ft_putstr_capitalized(char *str);
double			double_pow(double nbr, int times);

double			get_intstr_and_frac(long double nbr, char **int_str, int isneg);
int				get_fracstr_and_carryover(double frac_part, \
		char **frac_str, int prec);
int				increment_str(char **str, char type);
long double		get_doublenbr(t_flags *flags, va_list list);
int				print_intstr(char prepend, char *int_str, t_flags *flags);
int				print_weird(char *int_str, t_flags *flags);
double			set_infinity(long double nbr, char **int_str);
int				is_infinity(long double nbr);

#endif
