loop_hook(t_data *d)
    |
    +-- handle_player_moves(d)
    |       ├─ lit keypress -> calc déplacements
    |       ├─ apply_walk() (collision)
    |       └─ turn_player() (rotation)
    |
    +-- if need_redraw -> render_frame(d)
            |
            +-- (pour x=0..SCR_W-1)
            |       ├─ cameraX = 2*x/SCR_W - 1
            |       ├─ ray_build_dir()
            |       ├─ dda_init()
            |       ├─ while !hit -> dda_advance_until_hit()
            |       ├─ perp = dda_perp_distance()
            |       ├─ wall_x = get_wall_x()
            |       ├─ tex_x = get_texture_x()
            |       ├─ select_texture()
            |       └─ draw_textured_col()
            |
            +-- draw_crosshair()
            +-- draw_minimap(d)
                    ├─ selon cam.show_full_minimap
                    ├─ draw_minimap_cell(...)
                    ├─ draw_player_disc(...)
                    └─ draw_minimap_fov(...)
            |
            +-- request_redraw(d) => reset need_redraw=false
