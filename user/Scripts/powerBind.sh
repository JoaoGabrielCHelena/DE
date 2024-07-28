#!/bin/bash


PROMPT="zenity --list --title='Power Options' --text='' --column='' Shutdown Reboot Sleep Hibernate 'End Session'"

SELECTED=$(eval $PROMPT)

if [ -n "$SELECTED" ]; then
  if zenity --question --text="Are you sure you want to $SELECTED?"; then
    case "$SELECTED" in
      "Shutdown") shutdown now ;;
      "Reboot") reboot ;;
      "Sleep") systemctl suspend ;;
      "Hibernate") systemctl hibernate ;;
      "End Session") echo "did it" && pkill X ;;
    esac
  fi
fi
