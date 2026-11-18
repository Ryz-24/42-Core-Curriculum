/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:48:35 by ralhoura          #+#    #+#             */
/*   Updated: 2026/08/18 17:48:35 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/* Twice the area of triangle abc, computed exactly on the raw values
   (coordinate * 256) in a long. No division by 2 and no float, so
   nothing is rounded: equal areas really compare equal. */
static long	doubleArea(Point const &a, Point const &b, Point const &c)
{
	long	ax = a.getX().getRawBits();
	long	ay = a.getY().getRawBits();
	long	bx = b.getX().getRawBits();
	long	by = b.getY().getRawBits();
	long	cx = c.getX().getRawBits();
	long	cy = c.getY().getRawBits();
	long	area = ax * (by - cy) + bx * (cy - ay) + cx * (ay - by);

	if (area < 0)
		area = -area;
	return (area);
}

/* point is strictly inside when the three small triangles it makes
   with the edges add up to the big one. A small triangle of area 0
   means point is on an edge or a vertex: that counts as outside. */
bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	long	abc = doubleArea(a, b, c);
	long	abp = doubleArea(a, b, point);
	long	apc = doubleArea(a, point, c);
	long	pbc = doubleArea(point, b, c);

	if (abp == 0 || apc == 0 || pbc == 0)
		return (false);
	return (abc == abp + apc + pbc);
}
