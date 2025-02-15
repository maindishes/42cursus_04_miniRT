/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 05:25:45 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/20 17:47:09 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pixel_color(t_xpm_img xpm_img, int x, int y)
{
	char	*dst;

	x = clamp(x, 0, xpm_img.w - 1);
	y = clamp(y, 0, xpm_img.h - 1);
	dst = xpm_img.addr + (y * xpm_img.size + x * (xpm_img.bpp / 8));
	return (*(unsigned int *)dst);
}

t_vec3	change_basis(t_vec3 v1, t_vec3 v2, t_vec3 v3, t_vec3 vec)
{
	t_vec3	normal;

	normal.x = v1.x * vec.x + v2.x * vec.y + v3.x * vec.z;
	normal.y = v1.y * vec.x + v2.y * vec.y + v3.y * vec.z;
	normal.z = v1.z * vec.x + v2.z * vec.y + v3.z * vec.z;
	return (normal);
}

t_vec3	normal_mapping(double u, double v, t_vec3 uv_axis[2], t_hit hit)
{
	int		u2;
	int		v2;
	int		color;
	t_vec3	normal_color;

	u2 = u * hit.elem.tx->bmp_map.w;
	v2 = (1.0 - v) * hit.elem.tx->bmp_map.h;
	color = get_pixel_color(hit.elem.tx->bmp_map, u2, v2);
	normal_color = color_to_vec3(color);
	normal_color = vsub(vscale(normal_color, 2), create_vec3(1, 1, 1));
	return (change_basis(uv_axis[0], uv_axis[1], hit.nv, normal_color));
}

int	image_mapping(double u, double v, t_xpm_img img_map)
{
	int		u2;
	int		v2;
	int		color;

	u2 = u * img_map.w;
	v2 = (1.0 - v) * img_map.h;
	color = get_pixel_color(img_map, u2, v2);
	return (color);
}

int	texture_mapping(t_hit *hit)
{
	double	u;
	double	v;
	t_vec3	uv_axis[2];

	if (hit->elem.type == PL)
		uv_mapping_plane(&u, &v, uv_axis, *hit);
	if (hit->elem.type == SP)
		uv_mapping_sphere(&u, &v, uv_axis, *hit);
	if (hit->elem.type == CY)
		uv_mapping_cylinder(&u, &v, uv_axis, *hit);
	if (hit->elem.type == CON)
		uv_mapping_cone(&u, &v, uv_axis, *hit);
	if (hit->elem.tx && hit->elem.tx->bmp_map.ptr)
		hit->nv = normal_mapping(u, v, uv_axis, *hit);
	if (hit->elem.tx && hit->elem.tx->img_map.ptr)
		return (image_mapping(u, v, hit->elem.tx->img_map));
	if (hit->elem.checker_w > 0)
		return (checker_board_pattern_at(u, v, *hit));
	return (hit->elem.clr);
}
