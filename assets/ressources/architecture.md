modules et flux

Parsing -> remplit t_game
Init -> alloue t_data / t_gfx / textures / vecteurs joueur
Events -> modif t_keypress -> mouvement/rotation -> set need_redraw
Rendering -> lit player + game.map + textures -> frame
Minimap -> dépend de player.pos + game.map
Debug (print_*) -> ponctuel, inspecte structures
Utils -> nettoyage (clean_data), erreurs (print_error/exit_error)


          +-------------------+            lancement
          |      main.c       |  av ---> ./cub3D map.cub
          +---------+---------+
                    |
        +-----------v-----------+
        |      Parsing          |
        | parse_game_info()     |
        | parse_* (wall,rgb...) |
        | check_map()           |
        +-----------+-----------+
                    |
          +---------v---------+
          |    init/ setup    | init_game() -> init_data()
          | init_mlx()        | init_player_from_game()
          | set_texture()     |
          +---------+---------+
                    |
          +---------v---------+
          |  Boucle MLX       | mlx_loop_hook -> loop_hook()
          | (events + render) |
          +----+---------+----+
               |         |
      +--------v--+   +--v----------+
      |  Events    |   |  Render     |
      | on_key_*   |   | render_frame|
      | movement.c |   | (raycasting |
      | turn_player|   | + minimap)  |
      +-----+------+   +------+------+
            |                 |
            |                 v
            |         +---------------+
            |         |  Raycasting   |
            |         | dda_init()    |
            |         | dda_advance_* |
            |         | perp distance |
            |         +-------+-------+
            |                 |
            |                 v
            |         +---------------+
            |         | Texturing     |
            |         | select_texture|
            |         | get_wall_x    |
            |         | get_texture_x |
            |         | draw_textured |
            |         +-------+-------+
            |                 |
            |                 v
            |         +---------------+
            |         | Minimap       |
            |         | draw_minimap  |
            |         | draw_player   |
            |         | draw_minimap_fov|
            |         +---------------+
            |
            v
      +-----------+
      |  Utils    |
      | cleanup   |
      | exit_error|
      +-----------+
