#!/bin/bash
# Keyboard and trackpad are wonky, this is how I make em normal

xinput set-prop 11 "libinput Tapping Enabled" 1

xinput set-prop 11 "libinput Natural Scrolling Enabled" 1

setxkbmap -layout br -variant thinkpad
