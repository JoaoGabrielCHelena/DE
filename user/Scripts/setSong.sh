#!/bin/bash
# Bound to Ctrl + Shift + m
# shows all the songs in the current mpd playlist 
# and plays whichever is selected

find_index() {
    local value="$1"
    shift
    local arr=("$@")

    for i in "${!arr[@]}"; do
        if [[ "${arr[i]}" == "$value" ]]; then
            echo "$i"
            return 0
        fi
    done

    return 1  # Not found
}

OPTIONS=$(mpc playlist)

SELECTED=$(echo -e "$OPTIONS" | dmenu -l 15 -i -p "Pick from playlist")

mapfile -t PLAYLIST < <(mpc playlist)

if [ -n "$SELECTED" ]; then
  index=$(find_index "$SELECTED" "${PLAYLIST[@]}")
  index=$(("$index" + 1))

  mpc play "$index"
fi
