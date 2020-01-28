/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karatsuba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:21:18 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2020/01/28 15:09:03 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		del_split(t_split *split)
{
	del_bignum(split->hi);
	del_bignum(split->lo);
	free(split);
}

t_split		*init_split(t_bignum *val, int len)
{
	t_split		*split;
	int		half;

	if (!(split = (t_split*)malloc(sizeof(t_split))))
		return (0);
	half = val->size < len ? val->size : len;
	if (!(split->lo = str2bignum(val->value, 0, half - 1)))
	{
		free(split);
		return (NULL);
	}
	if (!(split->hi = half == val->size ? int2bignum(0) :
			str2bignum(val->value, half, val->size - 1)))
	{
		del_bignum(split->lo);
		free(split);
		return (NULL);
	}
	split->m = len;
	return (split);
}

t_bignum	*calc_b(t_split *x, t_split *y, t_bignum *a, t_bignum *c)
{
	t_bignum	*s1;
	t_bignum	*s2;
	t_bignum	*sub1;
	t_bignum	*sub2;
	t_bignum	*mul;

	if (!(s1 = bignum_add(x->hi, x->lo)))
		return (NULL);
	if (!(s2 = bignum_add(y->hi, y->lo)))
		return (NULL);
	if (!(mul = bignum_mul(s1, s2)))
		return (NULL);
	if (!(sub1 = bignum_sub(mul, a)))
		return (NULL);
	if (!(sub2 = bignum_sub(sub1, c)))
		return (NULL);
	del_bignum(s1);
	del_bignum(s2);
	del_bignum(sub1);
	del_bignum(mul);
	return (sub2);
}

t_bignum	*final_calculation(t_bignum *a, t_bignum *b, t_bignum *c, int m)
{
	t_bignum	*as;
	t_bignum	*bs;
	t_bignum	*sum;

	if (!(as = bignum_lshift(a, 2 * m)))
		return (NULL);
	if (!(bs = bignum_lshift(b, m)))
		return (NULL);
	if (!(sum = bignum_add(as, bs)))
		return (NULL);
	return (bignum_add(sum, c));
}

t_bignum	*get_params(t_split	*x, t_split *y)
{
	t_bignum	*a;
	t_bignum	*b;
	t_bignum	*c;
	t_bignum	*ptr;

	if (!(a = bignum_mul(x->hi, y->hi)))
		return (NULL);
	if (!(c = bignum_mul(x->lo, y->lo)))
		return (del_bignum(a));
	if (!(b = calc_b(x, y, a, c)))
		return (NULL);
	return (final_calculation(a, b, c, x->m));
}

t_bignum	*mul_karatsuba(t_bignum *n1, t_bignum *n2)
{
	t_split		*x;
	t_split		*y;
	t_bignum	*res;
	int		m;

	m = (unsigned int)(n1->size > n2->size ? n1->size : n2->size) >> 1u;
	if (!(x = init_split(n1, m)))
		return (NULL);
	if (!(y = init_split(n2, m)))
	{
		del_split(x);
		return (NULL);
	}
	return (get_params(x, y));
}