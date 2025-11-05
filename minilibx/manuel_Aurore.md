Init / fenêtre

mlx_init() → contexte MLX (à garder pour tout).

mlx_new_window(mlx, w, h, "title") → fenêtre.

mlx_destroy_window(mlx, win) + mlx_destroy_display(mlx) → nettoyage.


Images (le bon chemin pour dessiner vite)

mlx_new_image(mlx, w, h) → buffer hors-écran.

mlx_get_data_addr(img, &bpp, &size_line, &endian) → accès mémoire (écrire des pixels).

mlx_put_image_to_window(mlx, win, img, x, y) → affiche l’image.

mlx_destroy_image(mlx, img) → libère l’image.


Couleur

mlx_get_color_value(mlx, color) → adapte un 0x00RRGGBB au visuel courant (Linux/X11).

Le header que tu as collé confirme : “color is 0x00RRGGBB”.

color_rgb() + color_for_mlx().


Boucle / événements

mlx_loop(mlx) → boucle principale.

mlx_loop_hook(mlx, loop_fn, param) → callback à chaque frame (render).

mlx_key_hook(win, key_fn, param) → touches simples (press).

mlx_expose_hook(win, expose_fn, param) → redessiner si besoin.

mlx_hook(win, event, mask, fn, param) → générique (ex. fermeture fenêtre: event 17).
