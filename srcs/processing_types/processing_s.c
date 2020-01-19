/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 11:51:19 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/18 16:16:50 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_alignment_params(int align_params[3], t_ph *placeholder,
		const char *row_str)
{
	int len;

	len = ft_strlen(row_str);
	if (placeholder->precision != -1)
		len = (placeholder->precision < len ? placeholder->precision : len);
	FULL_SIZE = (int)max2(placeholder->width, len);
	PADDING = (int)max2(0, (int)placeholder->width - len);
}

static void	fill_string(t_vec **vec, t_ph *placeholder,
										int *align_params, const char *row_str)
{
	int				len;
	const t_bool	has_left_padding = (placeholder->flag & MINUS.code);
	const char		fill_char = (placeholder->flag & ZERO.code) ? '0' : ' ';

	len = FULL_SIZE - PADDING;
	if (!has_left_padding)
		while (PADDING > 0 && PADDING--)
			ft_vec_push(vec, fill_char);
	while (len--)
		ft_vec_push(vec, *row_str++);
	if (has_left_padding)
		while (PADDING > 0 && PADDING--)
			ft_vec_push(vec, ' ');
}

static void	override_placeholder(t_ph *placeholder)
{
	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	if (placeholder->flag & MINUS.code)
		placeholder->flag &= ~ZERO.code;
}

char		*processing_s(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	char		*row_string;
	int			align_params[3];

	ft_memset(align_params, 0, sizeof(align_params));
	row_string = va_arg(arg_ptr, char *);
	if (row_string == NULL)
		row_string = "(null)";
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder, row_string);
	fill_string(vec, placeholder, align_params, row_string);
	return (NULL);
}
