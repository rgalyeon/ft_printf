/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karatsuba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:21:18 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2020/01/27 14:21:18 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_split		*init_split(t_bignum *val, int len)
{
	t_split		*num;
	t_bignum	*lo;
	t_bignum	*hi;
	int		i;
	int		half;

	i = 0;
	half = val->size < len ? val->size : len;

	return ()
}

t_bignum	*mul_karatsuba(t_bignum *n1, t_bignum *n2)
{
	t_split	*x;
	t_split	*y;
	int		len;

	len = (unsigned int)(n1->size > n2->size ? n1->size : n2->size) >> 1u;
	x = init_split(n1, len);
	ft_printf("lo: %s\nhi: %s\nlen: %s\n", )
}