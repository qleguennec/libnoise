/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnoise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:50:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/14 16:18:23 by qle-guen         ###   ########.fr       */
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

cl_event		*noise_krl_exec(t_cl_info *cl, cl_kernel krl, t_noise *n, size_t *work_size);
t_cl_krl		*noise_krl_build(t_cl_info *cl, t_noise *n, void *data, size_t len);
void			noise_init(t_noise *n);

#endif
