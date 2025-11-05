/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:31:06 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/05 09:34:17 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "color.h"

/* =====================  🎨  PALETTE CUB3D  ===================== */

/* environnement global */
# define SKY             0xB8E2FF  /* bleu ciel clair, lumineux mais doux   */
# define FLOOR           0xF3E7C9  /* sable clair chaud                     */

/* murs et structures */
# define WALL_MAIN       0xA67C52  /* brun clair, effet bois/pierre         */
# define WALL_SHADOW     0x6E5336  /* version plus foncée pour ombres       */
# define WALL_ACCENT     0xD8BFA5  /* teinte claire pour relief             */

/* deco */
# define DOOR            0xC49058  /* brun doré                              */
# define WINDOW          0x8FC7FF  /* reflets bleutés                        */
# define METAL           0xAAB7B8  /* gris neutre                            */

/* Ambiance / effets spéciaux */
# define LIGHT_AMBIENT   0xFFF2CC  /* lumière chaude diffuse                 */
# define TORCH_GLOW      0xFFBF66  /* orange doux                            */
# define WATER            0x7FC8E3 /* bleu lagon                             */
# define GRASS            0x8FD17D /* vert doux et frais                     */

/* ++ (mini-map / joueurs / objets) */
# define PLAYER_COLOR    0xFF66B2  /* rose punchy                            */
# define ENEMY_COLOR     0xFF4040  /* rouge                                  */
# define ITEM_COLOR      0xF5E663  /* jaune clair pour items ramassables     */
# define MAP_WALL        0x5A5A5A  /* murs sur la mini-carte                 */
# define MAP_BG          0xEDEDED  /* fond de mini-carte                     */
