/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:17:11 by ihuang            #+#    #+#             */
/*   Updated: 2018/12/03 11:16:29 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./ft_printf.h"
#include "./libft/libft.h"
#include "./libft/get_next_line.h"
#include <fcntl.h>
#include <math.h>
#include "limits.h"
#define COUNT(a, b) (a != b) ? printf("BAD %d vs %d \n", a, b) : printf("\n");

int		main(void)
{
	char	*s;
	int		a;
	int		b;

	s = NULL;
	a = 0;
	b = 0;
	b = ft_printf("{%03c}", 0);
	COUNT(a, b);
	return (0);
}
