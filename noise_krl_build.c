/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:17:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/08 16:10:04 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

#define PRGNAME	"libnoise/noise2.cl"
#define KRLNAME	"noise2"

cl_kernel
	noise_krl_build
	(t_cl_info *cl
	, t_noise *n
	, void *data
	, size_t len)
{
	char		*mem;
	cl_kernel	krl;
	int			fd;
	size_t		alloc_size;
	size_t		offset2;
	size_t		offset;

	offset = len * sizeof(cl_float);
	offset2 = len * sizeof(cl_float2);
	alloc_size = offset + offset2 + n->ngrads * sizeof(*n->grads);
	if (!(fd = open(PRGNAME, O_RDONLY)))
		return (NULL);
	krl = cl_krl_build(cl, fd, KRLNAME, alloc_size);
	close(fd);
	cl_write(cl, offset, data, offset2);
	cl_write(cl, offset + offset2, n->grads, n->ngrads * sizeof(*n->grads));
	mem = (void *)cl->mem;
	CL_KRL_ARG(krl, 0, mem);
	mem += offset;
	CL_KRL_ARG(krl, 1, mem);
	mem += offset2;
	CL_KRL_ARG(krl, 2, mem);
	return (krl);
}
