/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:17:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 02:54:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

#define PRGNAME	"noise2.cl"
#define KRLNAME	"noise2"

int
noise_krl_build
	(t_cl_info *cl
	, t_noise *n
	, void *data
	, size_t size)
{
	cl_kernel	krl;
	int			fd;
	size_t		alloc_size;
	void		*mem;

	alloc_size = size
		+ n->ngrads * sizeof(*n->grads)
		+ sizeof(cl_uint)
		+ sizeof(cl_float);
	if (!(fd = open(PRGNAME, O_RDONLY)))
		return (0);
	krl = cl_krl_build(cl, fd, KRLNAME, alloc_size);
	close(fd);
	cl_write(cl, 0, data, size);
	cl_write(cl, size, n->grads, n->ngrads * sizeof(*n->grads));
	mem = cl->mem;
	CL_KRL_ARG(krl, 0, mem);
	mem = (cl_float2 *)mem + n->ngrads;
	CL_KRL_ARG(krl, 1, mem);
	return (!!krl);
}
