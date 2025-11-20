Pour une colonne i :

cameraX = (2*i / SCR_W) - 1
ray_dir = player.dir + player.plane * cameraX

Initialisation DDA:
  cell_row = (int)player.pos.y
  cell_col = (int)player.pos.x
  delta_row = fabs(1 / ray_dir.y)
  delta_col = fabs(1 / ray_dir.x)
  step_row / step_col selon signe des directions
  side_dist_row / side_dist_col initialisés

Boucle:
  if side_dist_row < side_dist_col:
      side_dist_row += delta_row
      cell_row += step_row
      side_hit_col = false
  else:
      side_dist_col += delta_col
      cell_col += step_col
      side_hit_col = true
  if map[cell_row][cell_col] == '1' => HIT

Distance perpendiculaire corrigée:
  perp = (side_hit_col)
        ? (cell_col - player.pos.x + (1 - step_col)/2) / ray_dir.x
        : (cell_row - player.pos.y + (1 - step_row)/2) / ray_dir.y

Hauteur de trait: line_h = (int)(SCR_H / perp)
Texture X:
  wall_x = get_wall_x(...)
  tex_x = get_texture_x(...)

Draw:
  draw_textured_col() -> boucle sur y top..bottom avec sampling vertical
