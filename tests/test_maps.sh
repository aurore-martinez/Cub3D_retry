#!/usr/bin/env bash
# Test script pour cub3D maps
# - compile le projet (make) si nécessaire
# - exécute ./cub3D pour chaque .cub dans assets/**
# - lance plusieurs valeurs de CUB3D_DEBUG (center, all, et quelques indices)
# - capture la sortie dans logs/<mapname>_*.log et produit un résumé

set -eu

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR"
CUB="${BUILD_DIR}/cub3D"
LOG_DIR="$ROOT_DIR/logs"
MAP_GLOBS=("$ROOT_DIR/assets/maps/*.cub" "$ROOT_DIR/assets/maps_chat/*.cub")
#  MAP_GLOBS=("$ROOT_DIR/assets/maps/*.cub" "$ROOT_DIR/assets/maps_chat/*.cub" "$ROOT_DIR/assets/maps_invalids/*.cub")
mkdir -p "$LOG_DIR"

echo "[test_maps] racine: $ROOT_DIR"

# Compile si exécutable manquant
if [ ! -x "$CUB" ]; then
    echo "[test_maps] exécutable introuvable, lance 'make' dans $BUILD_DIR"
    (cd "$BUILD_DIR" && make -j) || { echo "make a échoué"; exit 2; }
fi

run_with_debug() {
    local mapfile="$1"
    local dbg="$2"
    local outlog="$3"
    echo "[run] map=$(basename "$mapfile") debug=$dbg -> $outlog"
    # on limite le run à 2s pour éviter d'attendre la fenêtre interactive
    CUB3D_DEBUG="$dbg" timeout 2s "$CUB" "$mapfile" > "$outlog" 2>&1 || true
}

summary_file="$LOG_DIR/summary.txt"
: > "$summary_file"

for glob in "${MAP_GLOBS[@]}"; do
    for map in $glob; do
        [ -f "$map" ] || continue
        base=$(basename "$map" .cub)
        # Tests de base : center, all, et quelques colonnes (0, 100, 320)
        run_with_debug "$map" "center" "$LOG_DIR/${base}_center.log"
        run_with_debug "$map" "all" "$LOG_DIR/${base}_all.log"
        run_with_debug "$map" "0" "$LOG_DIR/${base}_col0.log"
        run_with_debug "$map" "100" "$LOG_DIR/${base}_col100.log"
        run_with_debug "$map" "320" "$LOG_DIR/${base}_col320.log"

        # résumé simple
        echo "== Map: $base ==" >> "$summary_file"
        for f in "$LOG_DIR/${base}"*.log; do
            echo "---- $(basename "$f") ----" >> "$summary_file"
            # ajouter un extrait
            head -n 50 "$f" >> "$summary_file" || true
            echo "" >> "$summary_file"
            # détecter crash/erreur
            if grep -qiE "segfault|traceback|error|fatal|panic|abort" "$f"; then
                echo "!! Potential crash / error found in $(basename "$f")" >> "$summary_file"
            fi
            # check pour message print_ray_debug out-of-range
            if grep -q "print_ray_debug: column_index" "$f"; then
                echo "!! print_ray_debug reported out-of-range column in $(basename "$f")" >> "$summary_file"
            fi
        done
    done
done

echo "Logs saved in $LOG_DIR"
echo "Summary: $summary_file"

exit 0
