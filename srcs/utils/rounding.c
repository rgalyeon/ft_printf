/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:01:48 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/28 17:06:21 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

	index = num->size - integral - prec;
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
