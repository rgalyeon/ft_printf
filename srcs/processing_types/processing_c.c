/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:32:32 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/19 22:00:20 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_alignment_params(int align_params[3], t_ph *placeholder)
{
	const int len = 1;

	placeholder->width = placeholder->width == -1 ? 0 : placeholder->width;
	PADDING = (int)max2(0, (int)placeholder->width - len);
}

static void	fill_string(t_vec **vec, t_ph *placeholder,
		int *align_params, const char row_char)
{
	const t_bool	has_left_padding = (placeholder->flag & MINUS.code);
	const char		fill_char = (placeholder->flag & ZERO.code) ? '0' : ' ';

	if (!has_left_padding)
		while (PADDING > 0 && PADDING--)
			ft_vec_push(vec, fill_char);
	ft_vec_push(vec, row_char);
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

char		*processing_c(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	char	row_char;
	int		align_params[3];

	row_char = (placeholder->type == 'c') ? (char)va_arg(arg_ptr, int) :
														(char)placeholder->type;
	ft_memset(align_params, 0, sizeof(align_params));
	override_placeholder(placeholder);
	get_alignment_params(align_params, placeholder);
	fill_string(vec, placeholder, align_params, row_char);
	return (NULL);
}
