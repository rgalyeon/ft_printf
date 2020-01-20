/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 21:37:02 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/20 19:50:56 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function disable conflicting placeholder's parameters for u type
** Flag 0 ignored if precision or flag '-' given
** ' ', '+' doesn't work with unsigned conversion
** @param placeholder
** @param value
*/

static void	override_placeholder(t_ph *placeholder)
{
	placeholder->flag |= HASH.code;
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->precision != -1 || (placeholder->flag & MINUS.code))
		placeholder->flag &= ~ZERO.code;
	placeholder->flag &= ~(PLUS.code | SPACE.code);
}

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
		__uint128_t value, char *converted_value)
{
	int len;

	len = ft_strlen(converted_value);
	if (!(value) && (placeholder->precision >= 0))
		len = 0;
	ZERO_COUNT = (int)placeholder->precision - len;
	PADDING = (int)(placeholder->width - (max2(placeholder->precision, len)));
	if (placeholder->flag & HASH.code)
		PADDING -= 2;
}

static void	fill_string(t_vec **vec, t_ph *placeholder, int *align_params,
		char *converted_value)
{
	if (!(placeholder->flag & MINUS.code) && !(placeholder->flag & ZERO.code))
		while (PADDING > 0 && PADDING--)
			*vec = ft_vec_push(vec, ' ');
	if (placeholder->flag & HASH.code)
		*vec = ft_vec_string_push(vec, "0x");
	if (placeholder->flag & ZERO.code)
	{
		ZERO_COUNT = ZERO_COUNT < 0 ? PADDING : ZERO_COUNT + PADDING;
		PADDING = 0;
	}
	while (ZERO_COUNT > 0 && ZERO_COUNT--)
		*vec = ft_vec_push(vec, '0');
	*vec = ft_vec_string_push(vec, (!ft_strcmp(converted_value, "0") &&
			placeholder->precision >= 0) ? "" : converted_value);
	while (PADDING > 0 && PADDING--)
		*vec = ft_vec_push(vec, ' ');
}

char		*processing_p(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	__uint128_t	value;
	char		*converted_value;
	int			align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	value = (size_t)va_arg(arg_ptr, void *);
	if (!(converted_value = ft_itoa_base(value, 16)))
		return (NULL);
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder, value, converted_value);
	fill_string(vec, placeholder, align_params, converted_value);
	free(converted_value);
	return (NULL);
}
