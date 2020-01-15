/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:53:31 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/15 15:21:32 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//TODO подумать про длину сдвига поинтера после парсинга плейсхолдера

t_vec *parse_format(int *size_ptr, char *format, va_list arg_ptr)
{
	t_vec *output_string;
	char *placeholder_string;

	if (!(output_string = ft_vec_init(16)))
		exit(MALLOC_ERR);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			placeholder_string = parse_placeholder(&format, size_ptr, arg_ptr);
//			ft_vec_string_push(&output_string, placeholder_string);
		}
		else
		{
			ft_vec_push(&output_string, *format);
			++format;
		}
	}
	return (output_string);
}

int 	ft_vfprintf(int fd, const char *format, va_list arg_ptr)
{
	t_vec	*output_string;
	int		output_size;

	output_size = 0;
	output_string = parse_format(&output_size, (char *)format, arg_ptr);
//	if (output_size != -1)
//		write(fd, output_string->data, output_size);
	return (output_size);
}


