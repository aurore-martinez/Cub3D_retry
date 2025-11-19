/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:16:17 by aumartin          #+#    #+#             */
/*   Updated: 2025/11/19 11:36:39 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/* Couleurs (format 0x00RRGGBB) */
# define BLACK      0x000000
# define WHITE      0xFFFFFF
# define RED        0xFF0000
# define GREEN      0x00FF00
# define BLUE       0x0000FF
# define YELLOW     0xFFFF00
# define CYAN       0x00FFFF
# define MAGENTA    0xFF00FF
# define GRAY       0x808080
# define DARKGRAY   0x404040
# define LIGHTGRAY  0xBFBFBF

/* Toujours plus de coul !! */
# define ORANGE        0xFFA500
# define DARKORANGE    0xFF8C00
# define BROWN         0x8B4513
# define SADDLEBROWN   0xA0522D
# define CHOCOLATE     0xD2691E
# define TAN           0xD2B48C
# define BEIGE         0xF5F5DC

# define DARKRED       0x8B0000
# define CRIMSON       0xDC143C
# define PINK          0xFFC0CB
# define HOTPINK       0xFF69B4
# define PURPLE        0x800080
# define VIOLET        0xEE82EE

# define DARKBLUE      0x00008B
# define STEELBLUE     0x4682B4
# define SKYBLUE       0x87CEEB
# define LIGHTBLUE     0xADD8E6

# define DARKGREEN     0x006400
# define FORESTGREEN   0x228B22
# define OLIVE         0x808000
# define LIMEGREEN     0x32CD32
# define PALEGREEN     0x98FB98

# define GOLD          0xFFD700
# define KHAKI         0xF0E68C
# define SILVER        0xC0C0C0

# define LIGHTYELLOW 0xFFFFE0
# define SOFTYELLOW  0xFFFF80

/* UI / Minimap colors */
# define UI_PLAYER_COLOR    GOLD          // Point joueur (jaune)
# define UI_FOV_COLOR       SOFTYELLOW    // Rayons FOV (jaune moyen)
# define UI_CROSSHAIR_COLOR WHITE        // Croix centrale (blanc)
# define UI_SPAWN_COLOR     TAN          // Spawn (beige foncé)
# define UI_FLOOR_COLOR     BEIGE        // Sol/vide (beige clair)

#endif
