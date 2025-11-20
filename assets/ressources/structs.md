t_data
 ├─ t_game *game
 │   ├─ char **map (height x width)
 │   ├─ t_pos player (spawn indices)
 │   ├─ t_element elements (textures paths + RGB)
 │   └─ int width / height
 ├─ t_vec player (position réelle + direction + plane)
 │   ├─ t_dpos pos (x,y double)
 │   ├─ t_dpos dir (vector direction)
 │   └─ t_dpos plane (cam plane FOV)
 ├─ t_gfx *gfx
 │   ├─ void *mlx / void *win
 │   ├─ t_img frame (buffer)
 │   ├─ t_cam cam (minimap settings)
 │   └─ t_tex texture (north/south/east/west + width/height)
 ├─ t_keypress key (états des touches)
 ├─ scr_w / scr_h
 └─ bool need_redraw
