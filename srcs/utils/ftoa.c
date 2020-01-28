/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:57:01 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/28 17:20:27 by mshagga          ###   ########.fr       */
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
	t_dbl2int	d2int;
	t_decimal	*num;
	int32_t		e2;
	__uint128_t	m2;

	if (!(num = (t_decimal*)malloc(sizeof(t_decimal))))
		return (NULL);
	d2int.dbl = val;
	num->sign = (d2int.bits >> (LDBL_MANTISSA_BITS + LDBL_EXPONENT_BITS)) & 1u;
	num->exponent = (d2int.bits >> LDBL_MANTISSA_BITS) &
					((1u << LDBL_EXPONENT_BITS) - 1u);
	num->mantissa = d2int.bits & MANTISSA_MASK;
	if (num->exponent == LDBL_EXP_MAX || (!num->exponent && !num->mantissa))
		return (num);
	num->exponent++;
	e2 = num->exponent == 0 ? 1 - LDBL_MANTISSA_BITS - LDBL_BIAS :
			num->exponent - LDBL_MANTISSA_BITS - LDBL_BIAS;
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
	{
		del_bignum(&n);
		return (NULL);
	}
	if (!(res = bignum_mul(num, n_pow)))
	{
		del_bignum(&n_pow);
		del_bignum(&n);
		return (NULL);
	}
	del_bignum(&n_pow);
	del_bignum(&n);
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
		{
			del_bignum(&m2);
			return (NULL);
		}
	}
	else
	{
		if (!(res = mul_by_pow(m2, 5, 0 - num->exponent)))
		{
			del_bignum(&m2);
			return (NULL);
		}
	}
	del_bignum(&m2);
	return (res);
}

char		*ftoa(long double val, int prec, uint8_t flag)
{
	t_decimal	*dec;
	t_bignum	*bign;
	char		*out;

	if (flag & LENGTH_LONG_DOUBLE && !(dec = ldbl2s(val)))
		return (NULL);
	else if (!(flag & LENGTH_LONG_DOUBLE) && !(dec = dbl2s(val)))
		return (NULL);
	if (dec->exponent == MAX_EXPONENT || dec->exponent == LDBL_EXP_MAX ||
		(!dec->exponent && !dec->mantissa))
		return (special_copy(dec, prec));
	if (!(bign = ryu(dec)))
	{
		free(dec);
		return (NULL);
	}
	dbl_rounding(bign, dec, prec, dec->exponent + bign->size);
	if (!(out = out_format(bign, prec, dec->exponent + bign->size, dec->sign)))
	{
		del_dec_num(&dec, &bign);
		return (NULL);
	}
	del_dec_num(&dec, &bign);
	return (out);
}
