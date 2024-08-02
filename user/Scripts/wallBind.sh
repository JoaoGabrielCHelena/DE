#!/bin/bash
# Bound to Ctrl + Shift + w
# Lets tou select a folder in the ~/Backgrounds/ folder

SCRIPT_PATH="$HOME/Scripts/wallLoop.sh"

# Define the list of items and their prefixes (folder name)
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

DMENU_INPUT=""

for PREFIX in "${ORDER[@]}"; do
  ISCURRENT=""
  if [[ $PREFIX == $CURRENT ]]; then
    ISCURRENT=" (Current)"
  fi
  THEME="${THEMES[$PREFIX]}"
  DMENU_INPUT+="[$PREFIX] $THEME$ISCURRENT\n"
done

DMENU_INPUT=$(echo -e "$DMENU_INPUT" | sed '/^$/d')

SELECTED_THEME=$(echo -e "$DMENU_INPUT" | dmenu -i -p "Choose Wallpaper Set:")

SELECTED_PREFIX=$(echo "$SELECTED_THEME" | awk '{print substr($1, 2, length($1)-2)}')

if [[ -n "$SELECTED_PREFIX" ]]; then
  pkill -f 'wallLoop.sh' 

  "$SCRIPT_PATH" "$SELECTED_PREFIX"
fi
