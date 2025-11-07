/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:00:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/06 09:32:31 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Affiche le caractère présent dans la grille de jeu à la cellule
 * déterminée par r->cell_row et r->cell_col.
 * Paramètres :
 *  - d : contexte principal contenant la map (t_game)
 *  - r : structure DDA contenant les indices de cellule (cell_row, cell_col)
 * Comportement : si la cellule est hors-limites ou la ligne est NULL,
 *                affiche '?' pour indiquer un caractère inconnu.
 */
static void	print_map_char_at_hit(t_data *d, t_dda *r)
{
	char	ch;
	int		len;

	ch = '?';
	if (r->cell_row >= 0 && r->cell_col >= 0)
	{
		if (d->game->map[r->cell_row])
		{
			len = (int)ft_strlen(d->game->map[r->cell_row]);
			if (r->cell_col < len)
				ch = d->game->map[r->cell_row][r->cell_col];
		}
		printf(" map char at hit = %c\n", ch);
	}
}

/*
 * Affiche des statistiques simples sur la map :
 * - largeur/hauteur (données de t_game)
 * - longueur minimale, maximale et moyenne des lignes (utile pour les maps "irrégulières")
 * - nombre total de murs ('1') trouvés dans la grille
 * La fonction est sûre : retourne immédiatement si g ou g->map est NULL.
 */
void	print_map_stats(t_game *g)
{
	int		i;
	int		min_len;
	int		max_len;
	long	total_len;
	int		rows;
	int		walls;

	if (!g || !g->map)
		return ;
	rows = g->height;
	min_len = INT_MAX;
	max_len = 0;
	total_len = 0;
	walls = 0;
	i = 0;
	while (i < rows)
	{
		int len = g->map[i] ? (int)ft_strlen(g->map[i]) : 0;
		int j = 0;
		if (len < min_len)
			min_len = len;
		if (len > max_len)
			max_len = len;
		total_len += len;
		while (j < len)
		{
			if (g->map[i][j] == '1')
				walls++;
			j++;
		}
		i++;
	}
	if (rows == 0)
		rows = 1;
	printf("map: width=%d height=%d\n", g->width, g->height);
	printf("line len: min=%d max=%d avg=%.2f\n", min_len, max_len, (double)total_len / (double)rows);
	printf("total walls: %d\n", walls);
}

/*
 * Affiche une petite zone (patch) de la map centrée sur (center_row, center_col).
 * Paramètres :
 *  - g : pointeur vers la structure t_game contenant la map
 *  - center_row/center_col : cellule centrale autour de laquelle afficher
 *  - radius : rayon en cellules à afficher (ex. radius=1 → 3x3)
 * Utilité : inspection rapide locale sans ouvrir l'interface graphique.
 */
void	print_map_patch(t_game *g, int center_row, int center_col, int radius)
{
	int r;
	int c;
	int row_min;
	int row_max;
	int col_min;
	int col_max;

	if (!g || !g->map)
		return ;
	row_min = center_row - radius;
	row_max = center_row + radius;
	col_min = center_col - radius;
	col_max = center_col + radius;
	printf("map patch centered at (row=%d,col=%d) radius=%d:\n", center_row, center_col, radius);
	r = row_min;
	while (r <= row_max)
	{
		c = col_min;
		while (c <= col_max)
		{
			char ch = ' ';
			if (r >= 0 && r < g->height && g->map[r])
			{
				int len = (int)ft_strlen(g->map[r]);
				if (c >= 0 && c < len)
					ch = g->map[r][c];
			}
			if (r == g->player.y && c == g->player.x)
				printf("P");
			else
				printf("%c", ch == '\0' ? ' ' : ch);
			c++;
		}
		printf("\n");
		r++;
	}
}

/*
 * Routine de debug pour un rayon vertical (colonne d'écran) :
 *  - construit la direction du rayon pour la colonne demandée
 *  - initialise la DDA (position, step, side distances)
 *  - avance la DDA jusqu'à toucher un mur
 *  - affiche les informations principales (état DDA, cellule touchée, distance perpendiculaire, côté touché)
 * Paramètres :
 *  - d : contexte complet (player, game, gfx)
 *  - column_index : indice de colonne écran [0 .. scr_w-1]
 * Remarques : la fonction vérifie les bornes de column_index et retourne si invalide.
 */
void	print_ray_debug(t_data *d, int column_index)
{
	t_dda	r;
	double	cameraX;
	double	perp;
	bool	hit;

	if (!d || !d->game || !d->gfx)
		return ;
	if (column_index < 0 || column_index >= d->scr_w)
	{
		printf("print_ray_debug: column_index %d out of range\n", column_index);
		printf(" valid range: 0 .. %d\n", d->scr_w - 1);
		return ;
	}
	cameraX = 2.0 * column_index / (double)d->scr_w - 1.0;
	ray_build_dir(&d->player, cameraX, &r);
	dda_init(&d->player, &r);
	printf("--- ray debug for column %d ---\n", column_index);
	printf(" cameraX=%.6f\n", cameraX);
	print_dda(&r);
	hit = dda_advance_until_hit(d->game, &r);
	perp = dda_perp_distance(&r);
	if (hit)
		printf(" after advance: hit=1\n");
	else
		printf(" after advance: hit=0\n");
	if (r.side_hit_col)
		printf(" side=1 (col)\n");
	else
		printf(" side=0 (row)\n");
	printf(" cell=(%d,%d)\n", r.cell_row, r.cell_col);
	printf(" perp=%.6f\n", perp);
	/* Affiche le caractère stocké dans la cellule touchée par le rayon (si disponible) */
	print_map_char_at_hit(d, &r);
}
