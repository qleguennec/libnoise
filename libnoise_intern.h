/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnoise_intern.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:29:28 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 06:42:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNOISE_INTERN_H
# define LIBNOISE_INTERN_H

#include "libnoise.h"
#include "../libft/libft.h"

#define HASH(x) (((unsigned long)(x * (double)n->k)) % (unsigned long)n->ngrads)

#endif
