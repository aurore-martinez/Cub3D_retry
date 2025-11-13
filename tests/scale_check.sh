#!/usr/bin/env bash
# Automated helper script to run a subset of the CUB3D peer-eval checklist.
# It runs only the checks that can be automated non interactively on a local machine.
# For interactive checks (window open, key presses, visual smoothness) the script
# prints manual steps to perform.
# Usage: ./tests/scale_check.sh

set -eu
cd "$(dirname "${BASH_SOURCE[0]}")/.." || exit 1
ROOT=$(pwd)
EXE="$ROOT/cub3D"
MAP_GOOD="assets/maps/map_test3.cub"
INVALID_DIR="assets/maps_invalids"
REPORT="tests/scale_check_report.txt"
VALGRIND_LOG="tests/valgrind_scale.log"
BMP_GLOB="screenshot_*.bmp screenshot.bmp *.bmp"

echo "CUB3D automated scale helper" > "$REPORT"
echo "Project root: $ROOT" >> "$REPORT"

ok() { echo "[OK]  $1" | tee -a "$REPORT"; }
fail() { echo "[FAIL] $1" | tee -a "$REPORT"; }
skip() { echo "[SKIP] $1" | tee -a "$REPORT"; }
info() { echo "[INFO] $1" | tee -a "$REPORT"; }

# 1) Build
info "1) Running make..."
if make -C "$ROOT" -j > /dev/null 2>&1; then
    ok "make succeeded"
else
    fail "make failed"
    echo "Aborting further automated checks." >> "$REPORT"
    exit 1
fi

# 2) Executable name
info "2) Checking executable name and presence"
if [ -x "$EXE" ]; then
    ok "Found executable: $EXE"
else
    fail "Executable '$EXE' not found or not executable"
fi

# 3) Filename extension handling (should return non-zero on wrong ext)
info "3) Running with wrong extension to check error handling"
TMP_OUT=$(mktemp)
set +e
"$EXE" "assets/maps/map_test3.txt" > "$TMP_OUT" 2>&1
status=$?
set -e
if [ $status -ne 0 ]; then
  ok "Program rejected wrong extension (exit code $status)"
else
  fail "Program accepted a .txt file (expected to reject wrong extension)"
  echo "--- stdout/stderr ---" >> "$REPORT"
  cat "$TMP_OUT" >> "$REPORT"
  echo "--- end ---" >> "$REPORT"
fi
rm -f "$TMP_OUT"

# 4) Invalid map files should return error (we expect non-zero)
info "4) Testing invalid maps in $INVALID_DIR"
if [ -d "$INVALID_DIR" ]; then
  ALL_OK=true
  for f in "$INVALID_DIR"/*.cub; do
    [ -e "$f" ] || continue
    set +e
    "$EXE" "$f" > tests/invalid_map_tmp.out 2>&1
    rc=$?
    set -e
    if [ $rc -eq 0 ]; then
      fail "Invalid map $f did not cause program to exit with error (rc=0)"
      echo "--- output for $f ---" >> "$REPORT"
      cat tests/invalid_map_tmp.out >> "$REPORT"
      echo "--- end ---" >> "$REPORT"
      ALL_OK=false
    else
      ok "Invalid map $f correctly rejected (rc=$rc)"
    fi
    rm -f tests/invalid_map_tmp.out
  done
  $ALL_OK || true
else
  skip "No invalid maps directory found ($INVALID_DIR)"
fi

# 5) --save (BMP) support: try couple of argument orders
info "5) Checking --save BMP behavior (if implemented)"
FOUND_BMP=false
# remove old BMPs we might have created earlier
sh -c "rm -f $ROOT/tests/*.bmp || true"
# check common invocation orders
for cmd in "\"$EXE\" --save \"$MAP_GOOD\"" "\"$EXE\" \"$MAP_GOOD\" --save"; do
  info " -> trying: $cmd"
  # run with timeout 6s to let program create BMP then exit
  if timeout 6s bash -c "$cmd" > /dev/null 2>&1; then
    # look for bmp files in project
    for pat in $BMP_GLOB; do
      for bmp in $ROOT/tests/$pat; do
        [ -e "$bmp" ] || continue
        ok "BMP generated: $bmp"
        FOUND_BMP=true
      done
    done
    if [ "$FOUND_BMP" = true ]; then
      break
    fi
  else
    info "Command returned non-zero or timed out"
  fi
done
if [ "$FOUND_BMP" = false ]; then
  skip "--save BMP either not implemented or did not produce an output (manual check required)"
fi

# 6) Run under valgrind for a short time to check for leaks (non exhaustive)
info "6) Running short valgrind session (timeout 6s) to check obvious leaks"
if command -v valgrind > /dev/null 2>&1; then
  rm -f "$VALGRIND_LOG"
  # run under timeout so the program doesn't run forever
  timeout 6s valgrind --leak-check=full --error-exitcode=1 --log-file="$VALGRIND_LOG" "$EXE" "$MAP_GOOD" > /dev/null 2>&1 || true
  if [ -f "$VALGRIND_LOG" ]; then
    if grep -q "definitely lost: 0 bytes" "$VALGRIND_LOG"; then
      ok "Valgrind: no definitely lost blocks reported (on short run)"
    else
      fail "Valgrind reported definite leaks or errors. See $VALGRIND_LOG"
    fi
  else
    skip "Valgrind log not produced; program may not have started or valgrind not available"
  fi
else
  skip "valgrind not installed"
fi

# 7) Manual/interactive checklist for the evaluator
cat >> "$REPORT" <<'EOF'

MANUAL CHECKS (please perform them and tick pass/fail)
- Window opens on program launch (when not using --save) and stays open
- The rendered scene is visible and consistent (maze view)
- Hiding/minimizing/maximizing keeps content consistent
- Press ESC or click close window: program must exit cleanly
- Arrow/WASD keys move/rotate player; holding a key moves continuously
- Movement should be smooth (playable)
- Textures/sprites change when config paths change; missing paths -> errors
- Floor/ceiling colors obey config
- Robustness tests: random args should not crash the program
- Modify map: valid maps should run, invalid should error
- Bonus features (only if mandatory perfect): check subject bonuses
EOF

info "All automated checks done. Report saved to $REPORT"
info "Open $REPORT to review results. Manual checks remain for interactive items."

echo
exit 0
