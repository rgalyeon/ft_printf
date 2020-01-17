/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:57:46 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/17 18:22:27 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"







char *processing_x(t_ph *placeholder, va_list arg_ptr)
{
	return NULL;
}

char *processing_c(t_ph *placeholder, va_list arg_ptr)
{
	return NULL;
}

char *processing_s(t_ph *placeholder, va_list arg_ptr)
{
	return NULL;
}

char *processing_p(t_ph *placeholder, va_list arg_ptr)
{
	return NULL;
}

char	*processing_types(t_ph *placeholder, va_list arg_ptr)
{
	const u_int8_t		type = placeholder->type;
	register u_int8_t	i;
	t_bool				was_processed;
	char 				*processed_string;

	i = 0;
	was_processed = FALSE;
	while (TYPE[i])
	{
		if (type == TYPE[i])
		{
			processed_string = PROCESSING_TYPE(i, placeholder, arg_ptr);
			was_processed = TRUE;
		}
		i++;
	}
	if (was_processed == FALSE)
		processed_string = PROCESSING_TYPE(CHAR, placeholder, arg_ptr);
	//TODO подумать про неизвестный тип
	return (processed_string);
}