/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:37:12 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/28 18:46:29 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

__int128	max2(__int128 a, __int128 b)
{
	return (a > b ? a : b);
}

void		del_dec_num(t_decimal **dec, t_bignum **num)
{
	free(*dec);
	del_bignum(num);
}

int			ft_uint_len(__int128 nb)
{
	int	len;

	nb = (nb < 0) ? -nb : nb;
	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
