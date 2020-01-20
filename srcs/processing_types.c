/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:57:46 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/19 22:22:35 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	processing_types(t_vec **vec, t_ph *placeholder, va_list arg_ptr)
{
	const u_int8_t		type = placeholder->type;
	register u_int8_t	i;
	t_bool				was_processed;

	i = 0;
	if (!type)
		return ;
	was_processed = FALSE;
	while (TYPE[i])
	{
		if (type == TYPE[i])
		{
			PROCESSING_TYPE(i, vec, placeholder, arg_ptr);
			was_processed = TRUE;
		}
		i++;
	}
	if (was_processed == FALSE)
		PROCESSING_TYPE(CHAR, vec, placeholder, arg_ptr);
}
