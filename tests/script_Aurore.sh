#!/usr/bin/env bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_full.log ./cub3D assets/maps/map_test3.cub
cat valgrind_full.log
grep -n \"still reachable\" -n valgrind_full.log
sed -n '/still reachable/,/====/p' valgrind_full.log
