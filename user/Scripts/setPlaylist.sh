#!/bin/bash
# Bound to Ctrl + Shift + k
# Shows a dmenu with playlist, i have them as foldes in ~/Music/ so 
# it just reads those folders and adds their files to the playlist

OPTIONS=$(cd ~/Music/ && ls -d */)

SELECTED=$(echo -e "$OPTIONS" | dmenu -l 8 -i -p "Pick playlist")

if [ -n "$SELECTED" ]; then
  echo "$SELECTED"
  mpc clear
  mpc add "$SELECTED"
  mpc play
fi
