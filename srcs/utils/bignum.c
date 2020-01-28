/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:39:14 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/25 23:50:31 by mshagga          ###   ########.fr       */
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

void		del_bignum(t_bignum *num)
{
	free(num->value);
	free(num);
}

//t_bignum	*str2bignum(char *str)
//{
//	t_bignum	*bignum;
//	size_t		len;
//	int			err;
//
//	len = ft_strlen(str);
//	if (!(bignum = (t_bignum*)malloc(sizeof(t_bignum))))
//		return (NULL);
//	if (!(bignum->value = ft_strdup(str)))
//	{
//		free(bignum);
//		return (NULL);
//	}
//	bignum->size = len;
//	return (bignum);
//}

t_bignum	*str2bignum(char *str, int start, int end)
{
	t_bignum	*num;
	size_t		len;

	len = !start && !end ? ft_strlen(str) : end - start + 1;
	if (!(num = (t_bignum*)malloc(sizeof(t_bignum))))
		return (NULL);
	if (!(num->value = (char*)malloc(sizeof(char) * len + 1)))
	{
		free(num);
		return (NULL);
	}
	ft_memcpy(num->value, str + start, len);
	num->value[len] = '\0';
	num->size = len;
	return (num);
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
	return (str2bignum((char*)buf, 0, 0));
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
t_bignum	*bignum_square(t_bignum	*n)
{
	int		tmp;
	int		carry;
	char	buf[2 * n->size];
	int		i;
	int		j;

	i = 0;
	ft_memset(buf, '\0', 2 * n->size + 1);
	while (n->value[i])
	{
		tmp = (!buf[2 * i] ? '0' : buf[2 * i]) - '0' + (n->value[i] - '0') * (n->value[i] - '0');
		buf[2 * i] = (tmp % 10) + '0';
		carry = tmp / 10;
		j = i + 1;
		while (n->value[j])
		{
			tmp = 2 * (n->value[j] - '0') * (n->value[i] - '0') + (!buf[i + j] ? '0' : buf[i + j]) - '0' + carry;
			buf[i + j++] = (tmp % 10) + '0';
			carry = tmp / 10;
		}
		if (carry)
			buf[i + n->size] = '0' + carry;
//		buf[i++ + n->size] = '0' + carry;
//		j = i;
		i++;
	}
	return (str2bignum(buf, 0 , 0));
}

t_bignum	*bignum_mul(t_bignum *n1, t_bignum *n2)
{
	int			tmp;
	int8_t		carry;
	char		buf[MAX_SIZE];
	int			i;
	int			j;

	if (!(i = 0) && !(j = 0) && bignum_cmp(n1, n2) < 0)
		ft_swap(n1, n2);
	ft_memset(buf, 0, MAX_SIZE);
	while (n1->value[i])
	{
		carry = 0;
		j = 0;
		while (n2->value[j])
		{
			tmp = C2INT(n1->value[i]) * C2INT(n2->value[j]) + C2INT(buf[i + j]) + carry;
			buf[i + j++] = INT2C(tmp % 10);
			carry = tmp / 10;
		}
		buf[i++ + j] = carry ? '0' + carry : '\0';
	}
//	if (res == n1)
//		free(n1);
//	else if (res == n2)
//		free(n2);
	return (str2bignum(buf, 0, 0));
}

t_bignum	*bignum_mul_by_int(t_bignum *n, uint64_t m)
{
	int			i;
	char		buf[MAX_SIZE];
	uint64_t	carry;
	uint64_t	tmp;

	i  = 0;
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
	return (str2bignum(buf, 0, 0));
}

t_bignum	*bignum_pow2(t_bignum *num)
{
	t_bignum	*ptr;

	ptr = bignum_mul(num, num);
	return (ptr);
}

//t_bignum	*bignum_pow(t_bignum *num, uint64_t p)
//{
//	t_bignum	*y;
//	t_bignum	*ptr;
//	t_bignum	*res;
//	t_bignum	*x;
//
//	if (p == 0)
//		return (int2bignum(1));
//	y = int2bignum(1);
//	x = str2bignum(num->value, 0);
//	while (p > 1)
//	{
//		if (p & 1u)
//		{
//			ptr = y;
//			y = bignum_mul(x, y);
//			del_bignum(&ptr);
//			ptr = x;
//			x = bignum_pow2(x);
//			p = (p - 1) >> 1u;
//			del_bignum(&ptr);
//		}
//		else
//		{
//			ptr = x;
//			x = bignum_pow2(ptr);
//			p = p >> 1u;
//			del_bignum(&ptr);
//		}
//	}
//	res = bignum_mul(x, y);
//	del_bignum(&y);
//	del_bignum(&x);
//	return (res);
//}

t_bignum	*bignum_pow(t_bignum *n, uint64_t p)
{
	t_bignum	*res;
	t_bignum	*s;

	if (p == 0)
		return (int2bignum(1));
	if (!(res = int2bignum(1)))
		return (NULL);
	if (!(s = str2bignum(n->value, 0, 0)))
		return (NULL);
	while (p)
	{
		if (p & 1u)
			res = bignum_mul(res, s);
		p >>= 1u;
		if (p)
			s = bignum_mul(s, s);
	}
	return (res);
}