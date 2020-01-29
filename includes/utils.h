/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:04:14 by mshagga           #+#    #+#             */
/*   Updated: 2020/01/29 16:28:42 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# define DBL_MANTISSA_BITS	52u
# define DBL_EXPONENT_BITS	11u
# define DBL_BIAS			1023u
# define LDBL_MANTISSA_BITS	64u
# define LDBL_EXPONENT_BITS	15u
# define LDBL_BIAS			16383u
# define LDBL_EXP_MAX		0x7FFF
# define LARGER				1
# define EQUAL				0
# define LESS				-1
# define MAX_SIZE			20000
# define MAX_EXPONENT		2047
# define NAN_V				"nan"
# define INF				"inf"
# define ZERO_V				"0"
# define MANTISSA_MASK		0xFFFFFFFFFFFFFFFF

typedef struct	s_double64
{
	uint64_t	mantissa : DBL_MANTISSA_BITS;
	uint64_t	exponent : DBL_EXPONENT_BITS;
	uint64_t	sign : 1;
}				t_double64;

typedef union	u_conv
{
	double		d;
	t_double64	u;
}				t_conv;

typedef union	u_dbl2int
{
	long double	dbl;
	__uint128_t	bits;
}				t_dbl2int;

typedef struct	s_bignum
{
	int			size;
	char		*value;
}				t_bignum;

typedef struct	s_decimal
{
	uint64_t	mantissa;
	int32_t		exponent;
	uint8_t		sign;
}				t_decimal;

/*
** Init functions
*/

t_bignum		*int2bignum(__uint128_t num);
t_bignum		*str2bignum(char *num);
void			del_bignum(t_bignum **num);

/*
** Arithmetic operations
*/

t_bignum		*bignum_add(t_bignum *n1, t_bignum *n2);
t_bignum		*bignum_mul(t_bignum *n1, t_bignum *n2);
t_bignum		*bignum_pow(t_bignum *num, uint64_t p);

/*
** Compare operations
*/

int8_t			bignum_cmp(t_bignum *n1, t_bignum *n2);
char			*ftoa(long double val, int prec, u_int8_t flag);

#endif
