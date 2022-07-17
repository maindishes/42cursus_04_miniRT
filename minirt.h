/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:50:03 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/17 18:50:55 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include "vec3.h"

/*
** vport_h : viewport_height
** vport_w : viewport_width
** focal_len: focal_length, distance from camera to the viewport
** origin : camera position
** l_l_c : lower_left_corner of viewport
*/
typedef struct s_cam
{
	double	aspect_ratio;
	double	vport_h;
	double	vport_w;
	double	focal_len;
	t_p3	origin;
	t_vec3	l_l_c;
	t_vec3	horizontal;
	t_vec3	vertical;
}				t_cam;

typedef struct s_ray
{
	t_p3	orig;
	t_vec3	dir;
}			t_ray;

typedef struct s_data {
	void	*img;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
}				t_data;

typedef struct s_minirt {
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		data;
	t_cam		cam;
}				t_minirt;

#endif