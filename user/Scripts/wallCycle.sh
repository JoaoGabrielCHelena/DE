#!/bin/bash


IMAGE_DIR="$HOME/Backgrounds"

if [ $# -eq 0 ]; then
  echo "Usage: $0 <prefix>"
  exit 1
fi

PREFIX=$1

IMAGE_LIST=($(ls -1 "$IMAGE_DIR/${PREFIX}/"*.jpg 2>/dev/null))

INDEX_FILE="$IMAGE_DIR/$PREFIX/.current_index"

if [ ${#IMAGE_LIST[@]} -eq 0 ]; then
  echo "No images found with prefix $PREFIX."
  exit 1
fi

if [[ -f "$INDEX_FILE" ]]; then
  CURRENT_INDEX=$(cat "$INDEX_FILE")
else
  CURRENT_INDEX=1
fi

TOTAL_IMAGES=${#IMAGE_LIST[@]}

if [[ $CURRENT_INDEX -gt $TOTAL_IMAGES ]]; then
  CURRENT_INDEX=1
fi

xwallpaper --zoom "${IMAGE_LIST[$((CURRENT_INDEX - 1))]}"

NEXT_INDEX=$((CURRENT_INDEX + 1))
if [[ $NEXT_INDEX -gt $TOTAL_IMAGES ]]; then
  NEXT_INDEX=1
fi

echo "$NEXT_INDEX" > "$INDEX_FILE"
