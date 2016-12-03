/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_krl_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:17:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/03 00:50:53 by qle-guen         ###   ########.fr       */
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
	, size_t size)
{
	int			fd;
	cl_kernel	krl;
	size_t		alloc_size;

	alloc_size = size + sizeof(cl_float2) + sizeof(cl_uint) + sizeof(cl_float);
	if (!(fd = open(PRGNAME, O_RDONLY)))
		return (0);
	krl = cl_krl_build(cl, fd, KRLNAME, alloc_size);
	close(fd);
	return (!!krl);
}
