/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:37:12 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/17 16:06:43 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__int128 max2(__int128 a, __int128 b)
{
	return (a > b ? a : b);
}

/**
**
** @param a - first value
** @param b - second value
** @param c - third value
** @return maximum of three values
*/

__int128		max3(__int128 a, __int128 b, __int128 c)
{
	__int128	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return max;
}

__int128		ft_uint_len(__int128 nb)
{
	int				len;

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