/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/24 00:25:45 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void	out_double(double num)
{
	t_conv		un;
	uint64_t	bits;
	int			i;

	i = 63;
	un.d = num;
	printf("Number: %f\n", num);
	ft_printf("%u %u %llu\n", un.u.sign, un.u.exponent, un.u.mantissa);
	ft_memcpy(&bits, &num, sizeof(double));
	while (i >= 0)
	{
		ft_printf("%d", (int)(bits >> i) & 1);
		if (i == 63)
			ft_printf(" ");
		else if (i == 52)
			ft_printf(" ");
		i--;
	}
	ft_printf("\n");
}

t_decimal	*d2s(double val)
{
	t_conv		dbl;
	int			e2;
	uint64_t	m2;
	t_decimal	*number;

	dbl.d = val;
	if (!(number = (t_decimal*)malloc(sizeof(t_decimal))))
		return (NULL);
	if (dbl.u.exponent == 0)
	{
		e2 = 1 - DBL_MANTISSA_BITS - 2;
		m2 = dbl.u.mantissa;
	}
	else
	{
		e2 = dbl.u.exponent - DBL_MANTISSA_BITS - DBL_BIAS;
		m2 = dbl.u.mantissa | (1ULL << DBL_MANTISSA_BITS);
	}
	number->mantissa = m2;
	number->exponent = e2;
	number->sign = dbl.u.sign;
	return (number);
}

t_bignum	*mul_by_pow(t_bignum *num, int base, uint64_t p)
{
	t_bignum	*res;
	t_bignum	*n;
	t_bignum	*n_pow;

	if (!(n = int2bignum(base)))
		return (NULL);
	if (!(n_pow = bignum_pow(n, p)))
		return (NULL);
	if (!(res = bignum_mul(num, n_pow)))
		return (NULL);
	del_bignum(&n_pow);
	del_bignum(&n);
	return (res);
}

char		*special_copy(t_decimal *dec)
{
	char	*res;
	int		len;

	len = dec->sign + dec->mantissa || dec->exponent ? 3 : 1;
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (dec->mantissa)
		ft_memcpy(res, NAN_V, sizeof(NAN_V));
	if (dec->sign)
		res[0] = '-';
	else if (dec->exponent)
		ft_memcpy(res + dec->sign, INF, sizeof(INF));
	else
		ft_memcpy(res + dec->sign, ZERO_V, sizeof(ZERO_V));
	return (res);
}

t_bignum	*ryu(t_decimal *num)
{
	t_bignum	*m2;
	t_bignum	*res;

	if (!(m2 = int2bignum(num->mantissa)))
		return (NULL);
	if (num->exponent >= 0)
	{
		if (!(res = mul_by_pow(m2, 2, num->exponent)))
			return (NULL);
	}
	else
		if (!(res = mul_by_pow(m2, 5, 0 - num->exponent)))
			return (NULL);
	del_bignum(&m2);
	return (res);
}

char	*out_format(t_bignum *number, int prec, int pow, int sign)
{
	char	*format;
	int		index;
	int		len;
	int		integral;
	int		size;

	index = 0;
	size = number->size - 1;
	len = prec + sign + (pow < 0 ? 2 : pow + 1);
	if (!(format = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (sign)
		format[index++] = '-';
	integral = pow <= 0 ? 1 : pow;
	while (integral--)
		format[index++] = pow <= 0 ? '0' : number->value[size--];
	if (prec > 0)
		format[index++] = '.';
	while (pow++ < 0 && prec-- > 0)
		format[index++] = '0';
	while (prec-- > 0)
		format[index++] = size >= 0 ? number->value[size--] : '0';
	format[index] = '\0';
	return (format);
}

int		dbl_rounding(t_bignum *number, t_decimal *dec, int prec, int integral)
{
	int	index;
	int	i;
	int	carry;

	integral = integral <= 0 ? 0 : integral;
	index = number->size - 1 - integral - prec;
	carry = 0;
	if (number->value[index] == '5')
	{
		i = index - 1;
		while (i >= 0 && number->value[i] == '0')
			i--;
		carry = number->value[i] ? 1 : 0;
	}
	while (carry && number->value[index])
	{
		carry = (number->value[index + 1] == '9');
		number->value[index] = '0';
		index++;
	}
	ft_printf("%c\n", number->value[index]);
	number->value[index]++;
	return (1);
}


// TODO free before return
char	*ftoa(double val, int prec)
{
	t_decimal	*dec;
	t_bignum	*all_num;
	char		*out;

	if (!(dec = d2s(val)))
		return (NULL);
	if (dec->exponent == MAX_EXPONENT || (!dec->exponent && !dec->mantissa))
		return (special_copy(dec));
	if (!(all_num = ryu(dec)))
		return (NULL);
	print_bignum(all_num, 0);
	dbl_rounding(all_num, dec, prec, dec->exponent + all_num->size);
	if (!(out = out_format(all_num, prec, dec->exponent + all_num->size, dec->sign)))
		return (NULL);
	free(dec);
	del_bignum(&all_num);
	return (out);
}



int main()
{
	t_conv	number;
	int		prec;

	number.d = 0.99995;
	prec = 4;
	out_double(number.d);
	printf("%s\n", ftoa(number.d, prec));
	printf("%.*f\n", prec, number.d);
	return (0);
}
