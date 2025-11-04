/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:20 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 13:58:38 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	Détruire proprement la fenêtre (on_destroy_event)
	- Déclenché quand l'utilisateur ferme la fenêtre
	- Libère les ressources MLX (image, fenêtre)
	- Termine le programme proprement (exit)

	Réagir aux touches du clavier (key_hook_event)
	- Détecte quelle touche est pressée
	- Si ESC est pressée : quitte proprement (comme on_destroy_event)
	- Sinon : appelle des fonctions pour :
		- Changer la vue (zoom, déplacement, échelle Z, taille tuiles)
		- Changer les couleurs
	- Rafraîchit ensuite l'affichage (re_render)
*/

int	on_destroy_event(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (engine->image.img_ptr)
		mlx_destroy_image(engine->mlx, engine->image.img_ptr);
	if (engine->window)
		mlx_destroy_window(engine->mlx, engine->window);
	if (engine->mlx)
		mlx_destroy_display(engine->mlx);
	free(engine->mlx);
	free_grid(engine->map.grid);
	exit(EXIT_SUCCESS);
	return (0);
}
/* void	on_destroy(t_engine *engine)
{
	if (engine->image.img_ptr)
		mlx_destroy_image(engine->mlx, engine->image.img_ptr);
	if (engine->window)
		mlx_destroy_window(engine->mlx, engine->window);
	exit(EXIT_SUCCESS);
} */

/* int	on_key_press(int key, t_engine *engine)
{
	if (key == KEY_ESC)
		on_destroy(engine);
	render_map(engine);
	return (0);
} */

int	on_key_press(int key, t_engine *engine)
{
	if (key == KEY_ESC)
		on_destroy_event(engine);
	else if (key == KEY_PLUS || key == KEY_MINUS
		|| key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN
		|| key == KEY_1 || key == KEY_2
		|| key == KEY_9 || key == KEY_0)
		change_view(key, engine);
	else if ((key >= KEY_Q && key <= KEY_Y) || (key >= KEY_A && key <= KEY_H))
		change_color(key, engine);
	render_map(engine);
	return (0);
}
