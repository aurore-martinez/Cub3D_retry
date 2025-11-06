/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:30:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/06 11:12:35 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
    Gestion centralisée des mouvements/rotations du joueur.
    Appelée depuis le handler de touches. Met à jour data->player.pos,
    data->player.dir et data->player.plane selon la touche pressée.
*/
static bool	can_move_to(t_game *g, double nx, double ny, double margin)
{
    int	r0;
    int	c0;
    int	r1;
    int	c1;
    int	r;
    int	c;

    if (!g || !g->map)
        return (false);
    r0 = (int)floor(nx - margin);
    c0 = (int)floor(ny - margin);
    r1 = (int)floor(nx + margin);
    c1 = (int)floor(ny + margin);
    r = r0;
    while (r <= r1)
    {
        c = c0;
        while (c <= c1)
        {
            if (is_wall(g, r, c))
                return (false);
            c++;
        }
        r++;
    }
    return (true);
}

static void	move_player(t_data *d, double nx, double ny, double margin)
{
    if (!d)
        return ;
    if (can_move_to(d->game, nx, d->player.pos.y, margin))
        d->player.pos.x = nx;
    if (can_move_to(d->game, d->player.pos.x, ny, margin))
        d->player.pos.y = ny;
}

static void	rotate_player(t_data *d, double angle)
{
    double	old_dir_x;
    double	old_plane_x;

    if (!d)
        return ;
    old_dir_x = d->player.dir.x;
    old_plane_x = d->player.plane.x;
    d->player.dir.x = d->player.dir.x * cos(angle) - d->player.dir.y * sin(angle);
    d->player.dir.y = old_dir_x * sin(angle) + d->player.dir.y * cos(angle);
    d->player.plane.x = d->player.plane.x * cos(angle) - d->player.plane.y * sin(angle);
    d->player.plane.y = old_plane_x * sin(angle) + d->player.plane.y * cos(angle);
}

void	handle_player_movement(int key, t_data *d)
{
    double	move_speed;
    double	rot_speed;
    double	nx;
    double	ny;
    double	margin;

    if (!d)
        return ;
    /* prefer per-player configured speeds when present */
    move_speed = d->player.move_speed > 0.0 ? d->player.move_speed : 0.15;
    rot_speed = d->player.rot_speed > 0.0 ? d->player.rot_speed : 0.12;
    margin = 0.2; /* player collision radius in cell units */

    if (key == KEY_W || key == KEY_UP)
    {
        nx = d->player.pos.x + d->player.dir.x * move_speed;
        ny = d->player.pos.y + d->player.dir.y * move_speed; 
        move_player(d, nx, ny, margin);
        return ;
    }
    if (key == KEY_S || key == KEY_DOWN)
    {
        nx = d->player.pos.x - d->player.dir.x * move_speed;
        ny = d->player.pos.y - d->player.dir.y * move_speed;
        move_player(d, nx, ny, margin);
        return ;
    }
    if (key == KEY_A)
    {
        nx = d->player.pos.x - d->player.plane.x * move_speed;
        ny = d->player.pos.y - d->player.plane.y * move_speed;
        move_player(d, nx, ny, margin);
        return ;
    }
    if (key == KEY_D)
    {
        nx = d->player.pos.x + d->player.plane.x * move_speed;
        ny = d->player.pos.y + d->player.plane.y * move_speed;
        move_player(d, nx, ny, margin);
        return ;
    }
    if (key == KEY_LEFT)
    {
        rotate_player(d, rot_speed);
        return ;
    }
    if (key == KEY_RIGHT)
    {
        rotate_player(d, -rot_speed);
        return ;
    }
}
