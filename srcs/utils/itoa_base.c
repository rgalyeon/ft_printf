/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:03:59 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/18 16:49:44 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_base(__int128 val, int base)
{
	char		*num_str;
	int			len;
	__int128	num;
	char		digit;

	len = val <= 0 && base == 10 ? 1 : 0;
	num = val;
	while (num)
	{
		num /= base;
		len++;
	}
	if (!(num_str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	num_str[len] = '\0';
	if (val == 0)
		num_str[0] = '0';
	while (val)
	{
		digit = val % base;
		num_str[--len] = digit < 10 ? '0' + digit : 'a' + digit - 10;
		val /= base;
	}
	return (num_str);
}
