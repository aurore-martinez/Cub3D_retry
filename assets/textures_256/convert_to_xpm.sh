#!/usr/bin/env zsh
# ------------------------------------------------------------
# Script ultra simple de conversion vers XPM (256x256).
# Modifie juste la variable FILTER_NAME ci-dessous pour tester
# différents filtres de rééchantillonnage ImageMagick.
# ------------------------------------------------------------
# Filtres intéressants à tester :
#   Mitchell  : équilibre netteté/douceur (recommandé par défaut)
#   Lanczos   : très net, bon pour détails fins
#   Catrom    : bicubique plus contrasté / edges plus marqués
#   Hermite   : léger adoucissement, rendu doux mais lisible
#   Spline    : très doux, peut flouter un peu (textures soft)
#   Point     : pixel art (ajouter aussi: -posterize 6 -dither None -colors 32)
#   Robidoux  : compromis différent (ImageMagick tuned)
#
# Exemple pixel art manuel (au lieu des FLAGS actuels) :
#   FILTER_NAME="Point"
#   EXTRA_FLAGS=( -resize 256x256 -posterize 6 -colors 32 -dither None -strip )
# Exemple très net contrasté :
#   FILTER_NAME="Lanczos" ; EXTRA_FLAGS=( -resize 256x256 -colors 64 -dither FloydSteinberg -modulate 110,100,100 -strip )
# Exemple doux :
#   FILTER_NAME="Spline" ; EXTRA_FLAGS=( -resize 256x256 -colors 64 -dither FloydSteinberg -strip )
# ------------------------------------------------------------

# Dossier source (images à convertir) et dossier cible
SRC_DIR="assets/img_to_convert"
OUT_DIR="assets/textures_256"
mkdir -p "$OUT_DIR" 2>/dev/null

# Choix du filtre (change juste cette valeur)
FILTER_NAME="Mitchell"

# Flags génériques (palette modérée + dithering propre)
FLAGS=( -resize 256x256^ -gravity center -extent 256x256 \
        -colors 64 -dither FloydSteinberg -colorspace sRGB -strip )

# Ajust esthétique léger (luminosité) — enlève/modifie si tu veux / si ça sature trop; descends 115 à 105 pour plus neutre
EXTRA_FLAGS=( -modulate 115,100,100 )

for f in $SRC_DIR/*.png $SRC_DIR/*.jpg $SRC_DIR/*.jpeg(N); do
  [ -e "$f" ] || continue
  name="${f##*/}"; base="${name%.*}"
  out="$OUT_DIR/${base}_256.xpm"
  if convert "$f" -auto-orient -filter "$FILTER_NAME" "${FLAGS[@]}" "${EXTRA_FLAGS[@]}" -background '#000000' -alpha remove -alpha off "$out"; then
    echo "OK: $out"
  else
    echo "FAIL: $f" >&2
  fi
done

echo "Terminé. Change FILTER_NAME=... puis relance pour comparer."
