/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnoise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:50:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 00:54:27 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNOISE_H
# define LIBNOISE_H

# include "../libcl/libcl.h"

typedef struct	s_noise
{
	cl_float2	*grads;
	cl_uint		ngrads;
	cl_float	seed;
}				t_noise;

int				noise_init_k(t_noise *n, unsigned int nseeds, unsigned int k);
int				noise_build_kernel(t_cl_info *cl, t_noise *n, void *out, size_t size);

#endif
