/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 01:46:20 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 03:16:19 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"

cl_event
*noise_krl_exec
	(t_cl_info *cl
	 , cl_kernel krl
	 , t_noise *n
	 , size_t *work_size)
{
	CL_KRL_ARG(krl, 3, n->ngrads);
	CL_KRL_ARG(krl, 4, n->seed);
	return (cl_krl_exec(cl, krl, 2, work_size));
}
