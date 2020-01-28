/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:56:20 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/28 18:47:38 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bignum	*bignum_square(t_bignum **num)
{
	t_bignum	**ptr;
	t_bignum	*res;

	ptr = num;
	res = bignum_mul(*num, *num);
	del_bignum(ptr);
	return (res);
}

t_bignum	*bignum_pow(t_bignum *num, uint64_t p)
{
	t_bignum	*res;
	t_bignum	*s;
	t_bignum	*ptr;

	if (p == 0)
		return (int2bignum(1));
	if (!(res = int2bignum(1)))
		return (NULL);
	if (!(s = str2bignum(num->value)))
		return (NULL);
	while (p)
	{
		if (p & 1u && (ptr = res))
		{
			res = bignum_mul(res, s);
			del_bignum(&ptr);
		}
		p >>= 1u;
		if (p)
			s = bignum_square(&s);
	}
	del_bignum(&s);
	return (res);
}

t_bignum	*bignum_mul(t_bignum *n1, t_bignum *n2)
{
	int			tmp;
	int8_t		carry;
	char		buf[MAX_SIZE];
	int			i;
	int			j;

	if (bignum_cmp(n1, n2) < 0)
		ft_swap(n1, n2);
	ft_memset(buf, 0, MAX_SIZE);
	i = 0;
	while (n1->value[i])
	{
		carry = 0;
		j = 0;
		while (n2->value[j])
		{
			tmp = (n1->value[i] - '0') * (n2->value[j] - '0') +
					(!buf[i + j] ? 0 : buf[i + j] - '0') + carry;
			buf[i + j++] = tmp % 10 + '0';
			carry = tmp / 10;
		}
		buf[i++ + j] = carry ? '0' + carry : '\0';
	}
	return (str2bignum(buf));
}

t_bignum	*bignum_add(t_bignum *n1, t_bignum *n2)
{
	char		buf[MAX_SIZE];
	int			i;
	int8_t		carry;
	int8_t		tmp;

	i = 0;
	carry = 0;
	if (bignum_cmp(n1, n2) == LESS)
		ft_swap(&n1, &n2);
	while (n1->value[i] && n2->value[i])
	{
		tmp = n1->value[i] - '0' + n2->value[i] - '0' + carry;
		carry = (tmp >= 10);
		buf[i] = tmp % 10 + '0';
		i++;
	}
	if (i < n1->size)
		while (n1->value[i])
		{
			buf[i] = n1->value[i];
			i++;
		}
	buf[i] = '\0';
	return (str2bignum((char*)buf));
}
