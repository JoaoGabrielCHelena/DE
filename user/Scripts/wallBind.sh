#!/bin/bash

# Path to the original cycleWall.sh script
SCRIPT_PATH="$HOME/Scripts/wallLoop.sh"

# Define the list of items and their prefixes
declare -A THEMES
THEMES=(
  ["E"]="Misc"
  ["D"]="Sakutake"
  ["C"]="Machiyoh"
  ["B"]="YuCong Tang"
  ["A"]="Chihuri"
)

# Item order from top to bottom
ORDER=("A" "B" "C" "D" "E")

PID=$(ps aux | grep 'cycleLoop.sh')

if [[ -n "$PID" ]]; then
  CURRENT=$(ps aux | grep 'wallLoop.sh' | awk '{print $13}' | head -n 1)
else
  CURRENT="none"
fi

ZENITY_CMD="zenity --list --title='Choose Wallpaper Set' --text='Select from the list' --column='ID' --column='Theme'"

for PREFIX in "${ORDER[@]}"; do
  ISCURRENT=""
  if [[ $PREFIX == $CURRENT ]]; then
    ISCURRENT=" (Current)"
  fi
  THEME="${THEMES[$PREFIX]}"
  ZENITY_CMD="$ZENITY_CMD '$PREFIX' '$THEME$ISCURRENT'"
done
#####################################
SELECTED_PREFIX=$(eval $ZENITY_CMD | awk '{print $1}')

for PREFIX in "${!THEMES[@]}"; do
  if [[ "${THEMES[$PREFIX]}" == "$SELECTED_PREFIX" ]]; then
    SELECTED_PREFIX="$PREFIX"
    break
  fi
done

if [[ -n "$SELECTED_PREFIX" ]]; then
  pkill -f 'wallLoop.sh' 

  "$SCRIPT_PATH" "$SELECTED_PREFIX"
fi
