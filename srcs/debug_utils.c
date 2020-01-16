/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:53:01 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/16 14:29:20 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void    print_bits(unsigned char octet)
{
	int z = 128, oct = octet;

	while (z > 0)
	{
		if (oct & z)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		z >>= 1;
	}
}

void	print_placeholder(t_ph *placeholder)
{
	write(1, "flag = ", 7);
	print_bits(placeholder->flag);
	printf("\n"
		   "width = %lld\n"
	       "precision = %d\n",
	       placeholder->width,
	       placeholder->precision);
	write(1, "length = ", 9);
	print_bits(placeholder->length);
	printf("\ntype = %c\n\n", placeholder->type);
}