/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:13 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/28 17:07:01 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*special_copy(t_decimal *dec, int prec)
{
	char	*res;
	int		len;

	len = dec->sign + (dec->mantissa || dec->exponent ? 3 : 1);
	len += !dec->exponent && !dec->mantissa && prec > 0 ? prec + 1 : 0;
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (dec->sign)
		res[0] = '-';
	if (dec->mantissa & (1ul << (LDBL_MANTISSA_BITS - 1)) - 1u)
		ft_memcpy(res, NAN_V, sizeof(NAN_V));
	else if (dec->exponent)
		ft_memcpy(res + dec->sign, INF, sizeof(INF));
	else
	{
		ft_memcpy(res + dec->sign, ZERO_V, sizeof(ZERO_V));
		if (prec > 0)
		{
			res[dec->sign + 1] = '.';
			ft_memset(res + dec->sign + 2, '0', prec);
			res[dec->sign + prec + 2] = '\0';
		}
	}
	free(dec);
	return (res);
}

char		*out_format(t_bignum *number, int prec, int pow, int sign)
{
	char	*format;
	int		index;
	int		len;
	int		integral;
	int		size;

	index = 0;
	size = !number->value[number->size] ? number->size - 1 : number->size;
	len = prec + sign + (pow <= 0 ? 2 : pow + 1);
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
