#include "libnoise.h"

float
lerp
	(float2 edges, float x)
{
	return (edges * (float2){1.0 - x, x});
}

float
dot_gradient
	(float2 *grads
	 , uint ngrads
	 , float seed
	 , float2 n
	 , int2 x)
{
	float2	grad;
	float2	d;

	seed *= x.x + x.y;
	if (seed < 0)
		seed = - seed;
	grad = grads[(int)seed % ngrads];
	d = x - n;
	d *= grad;
	return (d.x + d.y);
}

kernel void
noise2
	(global float2 *out
	 , constant float2 *grads
	 , constant uint ngrads,
	 , constant float seed)
{
	float2	d;
	float2	e0;
	float2	e1;
	float2	i;
	int2	n00;
	int2	n01;
	int2	n10;
	int2	n11;

	out += get_local_id(0) * get_local_id(1);
	n0 = as_int2(*out);
	n01 = n0 + (int2){0, 1};
	n10 = n0 + (int2){1, 0};
	n11 = n0 + (int2){1, 1};
	d = *out - n0;
	e0.x = dot_gradient(grads, ngrads, seed, n00, x);
	e0.y = dot_gradient(grads, ngrads, seed, n10, x);
	e1.x = dot_gradient(grads, ngrads, seed, n01, x);
	e1.y = dot_gradient(grads, ngrads, seed, n11, x);
	i = (float2){lerp(e0, d.x), lerp(e1, d.x)};
	return (lerp(i, d.y));
}
