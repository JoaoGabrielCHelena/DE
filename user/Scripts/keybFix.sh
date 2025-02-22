#!/bin/bash
# Keyboard is wonky, this is how I make it normal
setxkbmap -layout br -variant thinkpad

# Name of the sink you want to create
SINK_NAME="inverted"

# audio is inverted for some reason, this undoes it
if ! pactl list short sinks | grep -q "$SINK_NAME"; then
    ORIGINAL_SINK="alsa_output.pci-0000_07_00.6.analog-stereo"

    pactl load-module module-remap-sink sink_name="$SINK_NAME" master="$ORIGINAL_SINK" channels=2 master_channel_map=front-right,front-left channel_map=front-left,front-right

    sleep 1   
    pactl set-default-sink "$SINK_NAME"
fi
