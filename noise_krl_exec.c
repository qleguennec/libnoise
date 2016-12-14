/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 01:46:20 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/14 16:18:32 by qle-guen         ###   ########.fr       */
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
	return (cl_krl_exec(cl, krl, 2, work_size));
}
