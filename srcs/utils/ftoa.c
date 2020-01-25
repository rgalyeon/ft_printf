/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/25 23:37:15 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_decimal	*dbl2s(double val)
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
	e2 = dbl.u.exponent == 0 ? 1 - DBL_MANTISSA_BITS - DBL_BIAS :
			dbl.u.exponent - DBL_MANTISSA_BITS - DBL_BIAS;
	m2 = dbl.u.exponent == 0 ? dbl.u.mantissa :
			dbl.u.mantissa | (1ULL << DBL_MANTISSA_BITS);
	number->mantissa = m2;
	number->exponent = e2;
	return (number);
}

t_decimal	*ldbl2s(long double val)
{
	t_dbl2int	dbl2int;
	t_decimal	*num;
	int32_t		e2;
	__uint128_t	m2;

	if (!(num = (t_decimal*)malloc(sizeof(t_decimal))))
		return (NULL);
	dbl2int.dbl = val;
	num->sign = (dbl2int.bits >> (LDBL_MANTISSA_BITS + LDBL_EXPONENT_BITS)) & 1u;
	num->exponent = (dbl2int.bits >> LDBL_MANTISSA_BITS) & ((1u << LDBL_EXPONENT_BITS) - 1u);
	num->mantissa = dbl2int.bits & MANTISSA_MASK;
	if (num->exponent == LDBL_EXP_MAX)
		return (num);
	num->exponent++;
	e2 = num->exponent == 0 ? 1 - LDBL_MANTISSA_BITS - LDBL_BIAS :
			num->exponent - LDBL_MANTISSA_BITS - LDBL_BIAS; // ???
	m2 = num->exponent == 0 ? num->mantissa :
			num->mantissa | (1ul << (LDBL_MANTISSA_BITS - 1u));
	num->mantissa = m2;
	num->exponent = e2;
	return (num);
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
	if (dec->mantissa & (1ul << (LDBL_MANTISSA_BITS - 1)) - 1u)
		ft_memcpy(res, NAN_V, sizeof(NAN_V));
	else if (dec->exponent)
		ft_memcpy(res + dec->sign, INF, sizeof(INF));
	else
		ft_memcpy(res + dec->sign, ZERO_V, sizeof(ZERO_V));
	free(dec);
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

char	*zero(t_decimal *dec, int prec)
{
	int		len;
	int		index;
	char	*res;

	len = 1 + dec->sign + (prec > 0 ? prec + 1 : 0);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (dec->sign)
		res[0] = '-';
	res[dec->sign] = '0';
	index = dec->sign + 1;
	if (prec > 0)
		res[index++] = '.';
	while (prec > 0)
	{
		res[index++] = '0';
		prec--;
	}
	res[index] = '\0';
	free(dec);
	return (res);
}

char	*ftoa(long double val, int prec, uint8_t flag)
{
	t_decimal	*dec;
	t_bignum	*all_num;
	char		*out;

	if (!(flag & LENGTH_LONG_DOUBLE) && !(dec = dbl2s(val)))
		return (NULL);
	else if (!(dec = ldbl2s(val)))
		return (NULL);
	if (dec->exponent == MAX_EXPONENT || dec->exponent == LDBL_EXP_MAX)
		return (special_copy(dec));
	if ((!dec->exponent && !dec->mantissa) || (dec->exponent == ZERO_EXPONENT && dec->mantissa == ZERO_MANTISSA))
		return (zero(dec, prec));
	if (!(all_num = ryu(dec)))
	{
		free(dec);
		return (NULL);
	}
	dbl_rounding(all_num, dec, prec, dec->exponent + all_num->size);
	if (!(out = out_format(all_num, prec, dec->exponent + all_num->size, dec->sign)))
	{
		free(dec);
		del_bignum(&all_num);
		return (NULL);
	}
	free(dec);
	del_bignum(&all_num);
	return (out);
}
