/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/25 12:30:31 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <float.h>

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
	number->sign = dbl.u.sign;
	number->mantissa = dbl.u.mantissa;
	number->exponent = dbl.u.exponent;
	if (dbl.u.exponent == MAX_EXPONENT || (!dbl.u.exponent && !dbl.u.mantissa))
		return (number);
	e2 = dbl.u.exponent == 0 ? 1 - DBL_MANTISSA_BITS - 2 :
			dbl.u.exponent - DBL_MANTISSA_BITS - DBL_BIAS;
	m2 = dbl.u.exponent == 0 ? dbl.u.mantissa :
			dbl.u.mantissa | (1ULL << DBL_MANTISSA_BITS);
	number->mantissa = m2;
	number->exponent = e2;
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

	len = dec->sign + (dec->mantissa || dec->exponent ? 3 : 1);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (dec->sign)
		res[0] = '-';
	if (dec->mantissa)
		ft_memcpy(res, NAN_V, sizeof(NAN_V));
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

// TODO add precision to zero output
char	*out_format(t_bignum *number, int prec, int pow, int sign)
{
	char	*format;
	int		index;
	int		len;
	int		integral;
	int		size;

	index = 0;
	size = !number->value[number->size] ? number->size - 1 : number->size;
	len = prec + sign + (pow < 0 ? 2 : pow + 1);
	if (!(format = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (sign)
		format[index++] = '-';
	integral = pow <= 0 ? 1 : pow;
	while (integral-- && size >= 0)
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

int		banker(t_bignum *num, int index)
{
	int	i;

	i = index - 2;
	while (i > 0 && num->value[i] == '0')
		i--;
	if (i == 0 && num->value[i] == '0')
		return (num->value[index] % 2 == 1 ? 1 : 0);
	return (1);
}

int		dbl_rounding(t_bignum *num, t_decimal *dec, int prec, int integral)
{
	int			index;
	int			carry;

	index = num->size - integral - prec; // index stay on last digit to round
	if (index > num->size)
		return (0);
	if (index <= 0)
		return (0);
	if (num->value[index - 1] >= '0' && num->value[index - 1] <= '4')
		carry = 0;
	else
		carry = num->value[index - 1] == '5' ? banker(num, index) : 1;
	while (carry && num->value[index])
	{
		num->value[index] += num->value[index] == '9' ? -9 : 1;
		carry = (num->value[index++] == '0');
	}
	if (carry)
	{
		dec->exponent++;
		num->value[index] = '1';
	}
	return (0);
}

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
	dbl_rounding(all_num, dec, prec, dec->exponent + all_num->size);
	if (!(out = out_format(all_num, prec, dec->exponent + all_num->size, dec->sign)))
		return (NULL);
	free(dec);
	del_bignum(&all_num);
	return (out);
}

// TODO rounding && special cases
//int main()
//{
//	t_conv	number;
//	int		prec;
//
//	number.d = 44.5;
//	prec = 0;
//	out_double(number.d);
//	printf("ft_printf:\t%s\n", ftoa(number.d, prec));
//	printf("printf:\t\t%.*f\n", prec, number.d);
//	return (0);
//}
