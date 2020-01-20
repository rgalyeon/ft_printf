/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:53:31 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/20 19:41:05 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_free(t_vec *vec)
{
	if (vec)
	{
		if (vec->data)
			free(vec->data);
		free(vec);
	}
}

t_vec		*parse_format(int *size_ptr, char *format, va_list arg_ptr)
{
	t_vec	*output_string;

	if (!(output_string = ft_vec_init(32)))
		return (NULL);
	while (*format && *size_ptr != -1)
	{
		if (*format == '%')
		{
			++format;
			if (*format == '%')
			{
				if (!ft_vec_push(&output_string, '%'))
					return (NULL);
				++format;
			}
			else
				parse_placeholder(&output_string, &format, size_ptr, arg_ptr);
		}
		else if (!ft_vec_push(&output_string, *format++))
			return (NULL);
	}
	return (output_string);
}

int			ft_vfprintf(int fd, const char *format, va_list arg_ptr)
{
	t_vec	*output_string;
	int		output_size;

	output_size = 0;
	output_string = parse_format(&output_size, (char *)format, arg_ptr);
	if (output_size != -1 && output_string && output_string->data)
	{
		if (write(fd, output_string->data, output_string->total) == -1)
			output_size = -1;
		else
			output_size = output_string->total;
	}
	if (!output_string)
		output_size = -1;
	ft_printf_free(output_string);
	return (output_size);
}
