#!/usr/bin/env bash
# Test script pour cub3D maps
# - compile le projet (make) si nécessaire
# - exécute ./cub3D pour chaque .cub dans assets/**
# - exécute ./cub3D pour chaque .cub sans variables debug
# - capture la sortie dans logs/<mapname>.log et produit un résumé

set -eu

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR"
CUB="${BUILD_DIR}/cub3D"
LOG_DIR="$ROOT_DIR/tests/logs"
MAP_GLOBS=("$ROOT_DIR/assets/maps/*.cub" "$ROOT_DIR/assets/maps_invalids/*.cub")
#  MAP_GLOBS=("$ROOT_DIR/assets/maps/*.cub" "$ROOT_DIR/assets/maps_chat/*.cub" "$ROOT_DIR/assets/maps_invalids/*.cub")
mkdir -p "$LOG_DIR"

echo "[test_maps] racine: $ROOT_DIR"

# Compile si exécutable manquant
if [ ! -x "$CUB" ]; then
    echo "[test_maps] exécutable introuvable, lance 'make' dans $BUILD_DIR"
    (cd "$BUILD_DIR" && make -j) || { echo "make a échoué"; exit 2; }
fi

summary_file="$LOG_DIR/summary.txt"
: > "$summary_file"

for glob in "${MAP_GLOBS[@]}"; do
    for map in $glob; do
        [ -f "$map" ] || continue
        base=$(basename "$map" .cub)
        # Exécution simple (timeout 2s) sans CUB3D_DEBUG
        outlog="$LOG_DIR/${base}.log"
        echo "[run] map=$(basename "$map") -> $outlog"
        timeout 10s "$CUB" "$map" > "$outlog" 2>&1 || true

        echo "== Map: $base ==" >> "$summary_file"
        echo "---- $(basename "$outlog") ----" >> "$summary_file"
        head -n 50 "$outlog" >> "$summary_file" || true
        echo "" >> "$summary_file"
        if grep -qiE "segfault|traceback|error|fatal|panic|abort" "$outlog"; then
            echo "!! Potential crash / error found in $(basename "$outlog")" >> "$summary_file"
        fi
    done
done

echo "Logs saved in $LOG_DIR"
echo "Summary: $summary_file"

exit 0
