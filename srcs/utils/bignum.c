/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:39:14 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/28 16:03:23 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bignum	*int2bignum(__uint128_t num)
{
	t_bignum	*bignum;
	char		*num_str;

	if (!(bignum = (t_bignum*)malloc(sizeof(t_bignum))))
		return (NULL);
	if (!(num_str = ft_itoa_base(num, 10)))
	{
		free(bignum);
		return (NULL);
	}
	bignum->value = ft_strreverse(num_str);
	bignum->size = ft_strlen(bignum->value);
	return (bignum);
}

void		del_bignum(t_bignum **num)
{
	free((*num)->value);
	free(*num);
}

t_bignum	*str2bignum(char *str)
{
	t_bignum	*bignum;
	size_t		len;

	len = ft_strlen(str);
	if (!(bignum = (t_bignum*)malloc(sizeof(t_bignum))))
		return (NULL);
	if (!(bignum->value = ft_strdup(str)))
	{
		free(bignum);
		return (NULL);
	}
	bignum->size = len;
	return (bignum);
}

int8_t		bignum_cmp(t_bignum *n1, t_bignum *n2)
{
	int		i;

	i = n1->size == n2->size ? n1->size : -1;
	if (i < 0)
		return (n1->size > n2->size ? LARGER : LESS);
	while (i >= 0)
	{
		if (n1->value[i] == n2->value[i])
			i--;
		else
			return (n1->value[i] > n2->value[i] ? LARGER : LESS);
	}
	return (EQUAL);
}

t_bignum	*bignum_mul_by_int(t_bignum *n, uint64_t m)
{
	int			i;
	char		buf[MAX_SIZE];
	uint64_t	carry;
	uint64_t	tmp;

	i = 0;
	carry = 0;
	while (n->value[i])
	{
		tmp = (n->value[i] - '0') * m + carry;
		buf[i] = tmp % 10 + '0';
		carry = tmp / 10;
		i++;
	}
	while (carry)
	{
		buf[i++] = carry % 10 + '0';
		carry /= 10;
	}
	buf[i] = '\0';
	return (str2bignum(buf));
}
