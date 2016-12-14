/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:17:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/14 16:20:45 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include "../libft/libft.h"
#include "../libft/malloc.h"
#include <fcntl.h>
#include <unistd.h>

#define PRGNAME	"libnoise/noise2.cl"
#define KRLNAME	"noise2"

t_cl_krl
	*noise_krl_build
	(t_cl_info *cl
	, t_noise *n
	, void *data
	, size_t len)
{
	int			fd;
	t_cl_krl	*ret;

	if (!(fd = open(PRGNAME, O_RDONLY)))
		return (NULL);
	MALLOC_1(ret);
	cl_krl_init(ret, 3);
	ret->sizes[0] = len * sizeof(cl_float);
	ret->sizes[1] = len * sizeof(cl_float2);
	ret->sizes[2] = n->ngrads * sizeof(cl_float2);
	if (!(cl_krl_build(cl, ret, fd, KRLNAME)))
		return (NULL);
	close(fd);
	cl_write(cl, ret, 1, data);
	cl_write(cl, ret, 2, n->grads);
	CL_KRL_ARG(ret->krl, 3, n->ngrads);
	CL_KRL_ARG(ret->krl, 4, n->seed);
	return (ret);
}
