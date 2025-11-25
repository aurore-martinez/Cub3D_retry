#!/usr/bin/env bash

set -euo pipefail
EXE=${1:-./cub3D}
MAP=${2:-assets/maps/subject_map.cub}
TMPDIR="tests/tmp_defense"
mkdir -p "$TMPDIR"
LOG="$TMPDIR/defense.log"
: > "$LOG"

say() { printf "\n=== %s ===\n" "$1" | tee -a "$LOG"; }
ok() { echo "[OK] $*" | tee -a "$LOG"; }
warn() { echo "[WARN] $*" | tee -a "$LOG"; }
fail() { echo "[FAIL] $*" | tee -a "$LOG"; }
run() { echo "$ $*" | tee -a "$LOG"; "$@" >>"$LOG" 2>&1 || return $?; }
to_upper() { echo "$*" | tr '[:lower:]' '[:upper:]'; }
manual_test() {
  local msg=$(to_upper "$1")
  local secs=${2:-30}
  say "MANUEL: $msg (timeout ${secs}s)"
  echo ">>> $msg <<<"
  echo "LA FENETRE VA SE LANCER. REALISE L'ACTION DEMANDEE PUIS QUITTE." | tee -a "$LOG"
  if timeout "${secs}s" "$EXE" "$MAP" >/dev/null 2>&1; then
    ok "Action manuelle: $msg (terminée avant timeout)"
  else
    warn "Action manuelle: $msg (timeout écoulé ou rc!=0)"
  fi
}

########################################
say "1. Build / Makefile"
if [ -f Makefile ]; then
  run make -s || fail "make échoué"
  if [ -f cub3D ]; then ok "exécutable cub3D présent"; else fail "exécutable manquant"; fi
  # Vérifier non relink
  BEFORE=$(stat -c %Y cub3D)
  sleep 1
  run make -s
  AFTER=$(stat -c %Y cub3D)
  if [ "$BEFORE" = "$AFTER" ]; then ok "pas de relink inutile"; else warn "relink détecté"; fi
else
  fail "Makefile absent"
fi

########################################
say "2. Fichier configuration (.cub extension)"
if [[ "$MAP" != *.cub ]]; then fail "Nom de map n'a pas extension .cub"; else ok "Extension .cub OK"; fi
if [ -f "$MAP" ]; then ok "Map existe: $MAP"; else fail "Map introuvable: $MAP"; fi

########################################
say "3. Parsing éléments (NO SO WE EA F C)"
# Cherche chaque identifiant au moins une fois
for id in NO SO WE EA F C; do
  if grep -q "^$id" "$MAP"; then ok "$id trouvé"; else warn "$id manquant (vérifier map)"; fi
done

########################################
say "4. Test erreur: fichier invalide / extension"
BAD_EXT="$TMPDIR/bad.txt"
cp "$MAP" "$BAD_EXT" 2>/dev/null || true
if run "$EXE" "$BAD_EXT"; then warn "Pas d'erreur sur fichier extension .txt"; else ok "Erreur correcte (.txt rejeté)"; fi

########################################
say "5. Test erreur: clé dupliquée"
DUP_MAP="$TMPDIR/dup.cub"
{ grep -v '^NO' "$MAP"; grep '^NO' "$MAP" | head -n1; echo "NO ./fake_repeat.xpm"; } > "$DUP_MAP" 2>/dev/null || true
if run "$EXE" "$DUP_MAP"; then warn "Aucune erreur sur duplication NO"; else ok "Duplication détectée"; fi

########################################
say "6. Test erreur: chemin texture invalide"
BAD_TEX="$TMPDIR/badtex.cub"
sed 's/^NO .*/NO \/path\/invalide\/does_not_exist.xpm/' "$MAP" > "$BAD_TEX"
if run "$EXE" "$BAD_TEX"; then warn "Aucune erreur sur texture invalide"; else ok "Texture invalide détectée"; fi

########################################
say "7. Test couleur invalides"
BAD_COLOR="$TMPDIR/badcolor.cub"
sed 's/^F .*/F 999,999,999/' "$MAP" > "$BAD_COLOR"
if run "$EXE" "$BAD_COLOR"; then warn "Aucune erreur sur F hors range"; else ok "Couleur hors range détectée"; fi

########################################
say "8. Carte fermée (enclosure)"
# Simple heuristic: première et dernière ligne doivent être full '1'
FIRST_LINE=$(grep -v '^$' "$MAP" | tail -n +1 | sed -n '1p')
LAST_LINE=$(grep -v '^$' "$MAP" | sed -n '$p')
if echo "$FIRST_LINE" | grep -q '^[1 ]*$' && echo "$LAST_LINE" | grep -q '^[1 ]*$'; then ok "Première et dernière ligne murs"; else warn "Bords potentiellement ouverts"; fi

########################################
say "9. Lancement fenêtre (timeout 3s)"
echo "[INFO] Test démarrage fenêtre: ouverture rapide + timeout contrôlé" | tee -a "$LOG"
echo "[INFO] Si la fenêtre apparaît puis reste ouverte >3s ce sera marqué OK (timeout volontaire)." | tee -a "$LOG"
if timeout 3s bash -c "$EXE '$MAP'" >/dev/null 2>&1; then
  ok "Programme démarre et s'est terminé avant 3s (fenêtre OK)"
else
  rc=$?
  if [ $rc -eq 124 ]; then
    ok "Fenêtre lancée (processus actif, timeout volontaire rc=124)"
  else
    fail "Échec lancement programme (rc=$rc)"
  fi
fi

########################################
say "10. Mouvement & événements (MANUEL)"
manual_test "TEST LA FERMETURE DE LA FENETRE AVEC LA CROIX STP" 45
manual_test "TEST LA FERMETURE DE LA FENETRE AVEC LA TOUCHE ESC STP" 45
manual_test "TEST ROTATION GAUCHE/DROITE AVEC LES FLECHES ← → STP" 45
manual_test "TEST DEPLACEMENT EN LIGNE DROITE AVEC LES TOUCHES W A S D STP" 60

########################################
say "11. Textures (MANUEL + check chemins)"
for id in NO SO WE EA; do path=$(grep "^$id " "$MAP" | awk '{print $2}'); [ -n "$path" ] && [ -f "$path" ] && ok "Texture $id existe: $path" || warn "Texture $id introuvable: $path"; done

########################################
say "12. Couleurs sol/plafond"
F_LINE=$(grep '^F ' "$MAP" | head -n1 | awk '{print $2}')
C_LINE=$(grep '^C ' "$MAP" | head -n1 | awk '{print $2}')
if echo "$F_LINE" | grep -Eq '^[0-9]+,[0-9]+,[0-9]+'; then ok "Format F OK: $F_LINE"; else warn "Format F invalide"; fi
if echo "$C_LINE" | grep -Eq '^[0-9]+,[0-9]+,[0-9]+'; then ok "Format C OK: $C_LINE"; else warn "Format C invalide"; fi

########################################
say "13. Robustesse arguments fantaisistes"
if run "$EXE" a b c 2>/dev/null; then warn "Arguments multiples non rejetés"; else ok "Arguments fantaisistes -> erreur"; fi

########################################
say "14. Spam clavier (MANUEL)"
manual_test "SPAM CLAVIER: MARTELER DES TOUCHES AU HASARD STP (LE PROGRAMME DOIT RESTER STABLE)" 45

########################################
say "15. Leaks (optionnel valgrind)"
if command -v valgrind >/dev/null 2>&1; then
  echo "[INFO] Valgrind rapide..." | tee -a "$LOG"
  if timeout 20s valgrind --leak-check=full --error-exitcode=99 "$EXE" "$MAP" >"$TMPDIR/vg.log" 2>&1 || rc=$?; then
     rc=${rc:-0}
     if [ $rc -eq 99 ]; then fail "Leaks détectés (voir $TMPDIR/vg.log)"; else ok "Pas de leaks détectés (test rapide)"; fi
  fi
else
  warn "valgrind non installé, étape sautée"
fi

########################################
say "16. Bonus (MANUEL)"
manual_test "BONUS: TESTER COLLISIONS / MINIMAP / ROTATION A LA SOURIS (SI IMPLEMENTES)" 60

########################################
say "Bilan final"
if grep -F -q "[FAIL]" "$LOG"; then
  echo "Résultat: Des points à corriger (voir log: $LOG)"
else
  echo "Résultat: Aucun FAIL détecté (vérifications manuelles toujours nécessaires)"
fi

exit 0

#rm -rf tests/tmp_defense
