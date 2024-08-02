#!/bin/bash
# Changes wallpaper every 300 seconds

SCRIPT_PATH="$HOME/Scripts/wallCycle.sh"

if [ $# -eq 0 ]; then
  echo "Usage: $0 <prefix>"
  exit 1
fi

while true; do
  "$SCRIPT_PATH" "$1"

  sleep 300
done
