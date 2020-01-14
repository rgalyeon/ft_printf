/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:53:31 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/09 17:54:06 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_vec *parse_format(int *size, char *format)
{
	t_vec *output_string;
	char *placeholder_string;

	if (!(output_string = ft_vec_init(16)))
		exit(MALLOC_ERR);
	while (*format)
	{
		if (*format == '%')
		{
			placeholder_string = parse_placeholder(++format, size);
			ft_vec_string_push(&output_string, placeholder_string);
			format += ft_strlen(placeholder_string);
		}
		else
			++format;
	}
	return (output_string);
}

int 	ft_vfprintf(int fd, const char *format, ...)
{
	t_vec *output_string;
	int output_size;

	output_size = 0;
	output_string = parse_format(&output_size, (char *)format);
	if (output_size != -1)
		write(fd, output_string->data, output_size);
	return (output_size);
}


