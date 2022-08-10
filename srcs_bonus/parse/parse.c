/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyopar <junyopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:49:40 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/10 17:45:15 by junyopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cam(t_scene *scene, t_cam *cam)
{
	double	vp[2];
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	if (scene->xres < 0)
	{
		scene->xres = MAX_W;
		scene->yres = MAX_W;
	}
	if (!cam)
		put_error("cam is not declared");
	while (cam)
	{
		vp[1] = 2 * tan(cam->fov / 2 * M_PI / 180);
		vp[0] = vp[1] * (double)scene->xres / scene->yres;
		w = normalize(vscale(cam->nv, -1));
		set_uv_axis(w, &u, &v);
		cam->hor = vscale(u, vp[0]);
		cam->ver = vscale(v, vp[1]);
		cam->llc = vsub(cam->o, vscale(cam->hor, 0.5));
		cam->llc = vsub(cam->llc, vscale(cam->ver, 0.5));
		cam->llc = vsub(cam->llc, w);
		cam = cam->next;
	}
}

void	parse_resolution(t_scene *scene, char **str)
{
	if (scene->xres != -1 || scene->yres != -1)
		put_error("resolution declared multiple times");
	next(str);
	scene->xres = stof(str);
	scene->yres = stof(str);
	if (scene->xres < 0 || scene->xres < 0)
		put_error("resolution setting is out of range");
	scene->xres = clamp(scene->xres, MIN_W, MAX_W);
	scene->yres = clamp(scene->yres, MIN_W, MAX_W);
}

void	parse_scene(t_scene *scene, char *str)
{
	if (*str == '#')
		return ;
	if (*str == 'R' && *(str++))
		parse_resolution(scene, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(scene, &str);
	else if (*str == 'C' && *(str++))
		parse_camera(scene, &str);
	else if (*str == 'L' && *(str++))
		parse_light(scene, &str);
	else if (!ft_strncmp(str, "pl", 2) && *(str++) && *(str++))
		parse_plane(scene, &str);
	else if (!ft_strncmp(str, "sp", 2) && *(str++) && *(str++))
		parse_sphere(scene, &str);
	else if (!ft_strncmp(str, "cy", 2) && *(str++) && *(str++))
		parse_cylinder(scene, &str);
	else if (!ft_strncmp(str, "con", 3) && *(str++) && *(str++) && *(str++))
		parse_cone(scene, &str);
	else if (*str)
		put_error("invalid elment type");
}

void	parse_file(t_minirt *rt, char *av)
{
	int		fd;
	char	*str;
	int		len;

	len = ft_strlen(av);
	if (!av || len < 3 || av[len - 1] != 't'
		|| av[len - 2] != 'r' || av[len - 3] != '.')
		put_error("file format must be .rt");
	fd = open(av, O_RDONLY);
	if (fd == -1)
		put_error("fail to open file");
	str = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		parse_scene(&rt->scene, str);
		free(str);
	}
	free(str);
	set_cam(&rt->scene, rt->scene.cam);
}
