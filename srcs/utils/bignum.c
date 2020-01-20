/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:39:14 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/21 00:19:23 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// TODO Remove printf
// TODO Negative numbers logic

t_bignum	*int2bignum(__int128 num)
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

t_bignum	*str2bignum(char *str, uint8_t flag_rev)
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
	if (flag_rev)
		bignum->value = ft_strreverse(bignum->value);
	bignum->size = len;
	return (bignum);
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
	printf("n1 + n2:\n");
	print_bignum(n1);
	print_bignum(n2);
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
	return (str2bignum((char*)buf, 0));
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* return = a * b.  Caller is responsible for freeing memory.
 * Handling of negatives, and zeros is not here, since not needed.
 */
unsigned char *str_mult(const unsigned char *A, const unsigned char *B)
{
	int ax = 0, bx = 0, rx = 0, al, bl;
	unsigned char *a, *b, *r; /* result */

	al = strlen(A); bl = strlen(B);
	r = calloc(al + bl + 1, 1);
	/* convert A and B from ASCII string numbers, into numeric */
	a = malloc(al+1); strcpy(a, A); for (ax = 0; ax < al; ++ax) a[ax] -= '0';
	b = malloc(bl+1); strcpy(b, B); for (bx = 0; bx < bl; ++bx) b[bx] -= '0';

	/* grade-school method of multiplication */
	for (ax = al - 1; ax >= 0; ax--) {
		int carry = 0;
		for (bx = bl - 1, rx = ax + bx + 1; bx >= 0; bx--, rx--) {
//			ft_printf("a[%d]=%d\tb[%d]=%d\tr[%d]=%d\t%d\n", ax, a[ax], bx, b[bx], rx, r[rx], a[ax] * b[bx] + r[rx] + carry);
			int n = a[ax] * b[bx] + r[rx] + carry;
			r[rx] = (n % 10);
			carry = n / 10;
		}
		r[rx] += carry;
	}
	for (rx = 0; rx < al + bl; ++rx)
		r[rx] += '0';
	printf("result: %s\n", r);
	while (r[0] == '0')
		memmove(r, &r[1], al + bl);
	free(b); free(a);
	return r;
}

t_bignum	*bignum_mul(t_bignum *n1, t_bignum *n2)
{
	t_bignum	*res;
	int			tmp;
	int8_t		carry;
	char		*buf;
	int			i;
	int			j;

	if (!(buf = (char*)ft_memalloc(n1->size + n2->size + 1)))
		return (NULL);
	if (bignum_cmp(n1, n2) < 0)
		ft_swap(n1, n2);
	i = 0;
	j = 0;
	while (n1->value[i])
	{
		carry = 0;
		j = 0;
		while (n2->value[j])
		{
			tmp = C2INT(n1->value[i]) * C2INT(n2->value[j]) + C2INT(buf[i + j]) + carry;
			buf[i + j] = INT2C(tmp % 10);
			carry = tmp / 10;
			j++;
		}
		buf[i + j] = INT2C(carry);
		i++;
	}
	buf[i + j - 1] = '\0';
	return (str2bignum(buf, 0));
}

void		print_bignum(t_bignum *num)
{
	int		i;

	if (!num)
		return ;
	i = num->size;
	while (i >= 0)
		ft_printf("%c", num->value[i--]);
	ft_printf(" [%d]\n", num->size);
}

int main()
{
	t_bignum	*n1;
	t_bignum	*n2;
	t_bignum	*res;
	__uint128_t num = ((__uint128_t)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF;

	n1 = int2bignum(num);
	n2 = str2bignum("", 1);
	res = bignum_add(n1, n2);
	print_bignum(res);
	printf("%s\n", str_mult((const unsigned char*)"3617", (const unsigned char*)"13"));
	print_bignum(bignum_mul(n1, n1));
	return (0);
}