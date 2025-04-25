#!/bin/bash
# Bound to Ctrl + Shift + m
# shows all the songs in the current mpd playlist 
# and plays whichever is selected


OPTIONS=(
"stop"
"record | internal audio"
"record | microphone and internal audio"
"record | microphone audio"
"record | no audio"
)

SELECTED=$(printf "%s\n" "${OPTIONS[@]}" | dmenu -i -p "recording options")

OUTPUT_DIR="$HOME/Videos"
OUTPUT_FILE="$OUTPUT_DIR/screen_record_$(date +%Y%m%d_%H%M%S).mp4"
AUDIO_SOURCE=$(pactl list sources short | awk '/monitor/ {print $2; exit}')
AUDIO_INPUT=$(pactl list sources short | awk '/echosource/ {print $2; exit}')
FFMPEG_RECORD="ffmpeg -f x11grab -framerate 60 -s 1920x1080 -i :0.0"
FFMPEG_INTERNAL="-f pulse -i $AUDIO_SOURCE"
FFMPEG_MICROPHONE="-f pulse -i $AUDIO_INPUT"

PID_FILE="/tmp/ffmpeg_recording.pid"

if [ -n "$SELECTED" ]; then
  if [ "$SELECTED" == "stop" ]; then
      kill "$(cat "$PID_FILE")"
      rm -f "$PID_FILE"
  fi
  if [ -f "$PID_FILE" ]; then
    echo "Recording is already running!"
    exit 1
  fi
  case "$SELECTED" in
    "record | internal audio")
      FFMPEG_CMD="$FFMPEG_RECORD $FFMPEG_INTERNAL $OUTPUT_FILE"
      $FFMPEG_CMD & echo $! > "$PID_FILE"
      ;;

    "record | microphone and internal audio")
      FFMPEG_CMD="$FFMPEG_RECORD $FFMPEG_MICROPHONE $FFMPEG_INTERNAL   -map 0:v -map 1:a -map 2:a -c:v libx264 -preset ultrafast -crf 18
 -c:a aac -strict experimental -metadata:s:a:0 -metadata:s:a:1 -y $OUTPUT_FILE"
      $FFMPEG_CMD & echo $! > "$PID_FILE"
      ;;

    "record | microphone audio")
      FFMPEG_CMD="$FFMPEG_RECORD $FFMPEG_MICROPHONE $OUTPUT_FILE"
      $FFMPEG_CMD & echo $! > "$PID_FILE"
      ;;

    "record | no audio")
      FFMPEG_CMD="$FFMPEG_RECORD $OUTPUT_FILE"
      $FFMPEG_CMD & echo $! > "$PID_FILE"
      ;;

    *)
      echo "Invalid selection!"
      ;;
  esac
fi

