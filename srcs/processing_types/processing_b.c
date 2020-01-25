/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:48:18 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/25 20:17:16 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static __uint128_t	get_value_from_va_stack(u_int8_t length, va_list arg_ptr)
{
	__uint128_t	value;

	if (length & LENGTH_LONG_LONG)
		value = (unsigned long long)va_arg(arg_ptr, long long int);
	else if (length & LENGTH_LONG)
		value = (unsigned long)va_arg(arg_ptr, long int);
	else if (length & LENGTH_SHORT)
		value = (unsigned short)va_arg(arg_ptr, int);
	else if (length & LENGTH_CHAR)
		value = (unsigned char)va_arg(arg_ptr, int);
	else
		value = (unsigned)va_arg(arg_ptr, int);
	return (value);
}

/*
** Function for convert value in binary
** @param value - value from va_list
** @param placeholder
** @param buf - function write bits in buffer
*/

static void			get_bits(__uint128_t value, t_ph *placeholder, char *buf)
{
	uintmax_t		z;
	const u_int8_t	length = placeholder->length;
	register int	i;

	i = 1;
	z = 1;
	z <<= length & LENGTH_CHAR ? sizeof(char) * 8 - 1 : 0;
	z <<= length & LENGTH_SHORT ? sizeof(short int) * 8 - 1 : 0;
	z <<= length & LENGTH_LONG ? sizeof(long int) * 8 - 1 : 0;
	z <<= length & LENGTH_LONG_LONG ? sizeof(long long int) * 8 - 1 : 0;
	z <<= length == 0 ? sizeof(int) * 8 - 1 : 0;
	if (placeholder->type == 'b')
		while ((value & z) == 0 && z)
			z >>= 1 && i++;
	if (z == 0)
		*buf++ = '0';
	while (z > 0)
	{
		*buf++ = value & z ? '1' : '0';
		z >>= 1;
		if (placeholder->flag & g_flag[HASH].code && i % 8 == 0 && z != 0)
			*buf++ = ' ';
		i++;
	}
	*buf = '\0';
}

/*
** Function write in align_params array alignment params (padding,zero_pad, ...)
** @param align_params - array for writing parameters
** @param placeholder
** @param str_bits - value's bits in string
*/

static void			get_alignment_params(int align_params[3], t_ph *placeholder,
		char *str_bits)
{
	int len;

	len = ft_strlen(str_bits);
	align_params[PAD] = (int)(placeholder->width - len);
}

/*
** Function write processed string (placeholder) to vector
** @param vec - output string (vector)
** @param ph - placeholder
** @param align_params - array with padding params
** @param str_bits - value's bits in string
*/

static void			fill_string(t_vec **vec, t_ph *placeholder,
		int *align_params, char *str_bits)
{
	const char c = placeholder->flag & g_flag[ZERO].code ? '0' : ' ';

	if (!(placeholder->flag & g_flag[MINUS].code))
		while (align_params[PAD] > 0 && align_params[PAD]--)
			*vec = ft_vec_push(vec, c);
	ft_vec_string_push(vec, str_bits);
	while (align_params[PAD] > 0 && align_params[PAD]--)
		*vec = ft_vec_push(vec, ' ');
}

/*
** '%b' - type for print in binary;
** @param vec - output string
** @param placeholder
** @param arg_ptr - va_list
*/

void				processing_b(t_vec **vec, t_ph *placeholder,
															va_list arg_ptr)
{
	__uint128_t	value;
	int			align_params[3];
	char		str_bits[100];

	ft_memset(align_params, 0, sizeof(align_params));
	ft_memset(str_bits, 0, sizeof(str_bits));
	value = get_value_from_va_stack(placeholder->length, arg_ptr);
	get_bits(value, placeholder, str_bits);
	get_alignment_params(align_params, placeholder, str_bits);
	fill_string(vec, placeholder, align_params, str_bits);
}
