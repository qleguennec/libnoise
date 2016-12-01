/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnoise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:50:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 00:31:54 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNOISE_H
# define LIBNOISE_H

# ifndef NOISE_VAL_TYPE
#  define NOISE_VAL_TYPE float
# endif

# ifndef NOISE_DIM
#  define NOISE_DIM 2
# endif

# define NOISE_DIM_2		NOISE_DIM * NOISE_DIM

# include <stdlib.h>

typedef NOISE_VAL_TYPE	t_noise_unit;
typedef NOISE_VAL_TYPE	t_noise_val[NOISE_DIM];
typedef unsigned int	t_noise_u32[NOISE_DIM];

typedef struct			s_noise
{
	t_noise_val			*grads;
	unsigned int		ngrads;
	unsigned int		dim[NOISE_DIM];
	unsigned int		k;
	unsigned int		p;
	unsigned long		seed;
	size_t				ncols;
}						t_noise;

#endif
