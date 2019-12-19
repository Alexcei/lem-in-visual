/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:33:17 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 18:34:10 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			rotate(t_dot *dot, double alpha, double beta)
{
	double		x;
	double		y;

	x = dot->x;
	y = dot->y;
	dot->x = cos(beta) * x + sin(beta) * dot->z;
	dot->z = -sin(beta) * x + cos(beta) * dot->z;
	dot->y = cos(alpha) * y - sin(alpha) * dot->z;
	dot->z = sin(alpha) * y + cos(alpha) * dot->z;
}

t_dot			transformations(t_dot dot, t_data *data)
{
	dot.x -= (data->width - 1) / 2;
	dot.y -= (data->height - 1) / 2;
	dot.z -= (data->z_min + data->z_max) / 2;
	rotate(&dot, data->camera->alpha, data->camera->beta);
	dot.x *= data->camera->zoom;
	dot.y *= data->camera->zoom;
	dot.x += data->camera->x_offset;
	dot.y += data->camera->y_offset;
	return (dot);
}
