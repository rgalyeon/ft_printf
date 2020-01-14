/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_placeholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 22:47:47 by rgalyeon          #+#    #+#             */
/*   Updated: 2020/01/10 22:51:28 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *parse_placeholder(char *format, int *size)
{
	t_ph *placeholder;

	if (!(placeholder = (t_ph *)ft_memalloc(sizeof(t_ph))))
		exit(MALLOC_ERR);
	


	return NULL;
}