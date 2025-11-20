Minimap logic:
+----------------------------------------------------+
| calc tile_size (mm_tile_size / mf_tile_size)       |
| calc offsets (mm_off_x, mm_off_y)                  |
| if focus: limites (start/end) autour du joueur     |
| draw_minimap_cell() pour chaque cellule visible    |
| draw_player_disc() centré                         |
| draw_minimap_fov(): rayons ou cône                |
+----------------------------------------------------+
