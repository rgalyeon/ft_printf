/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:10:03 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/09 18:03:52 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct	s_ph
{
	int flag;
	int width;
	int precision;
	int length;
	int type;
}				t_ph;

int ft_printf(const char *format, ...);
int ft_vdprintf(int fd, const char *format, ...);


#endif
