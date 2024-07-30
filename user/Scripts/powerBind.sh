#!/bin/bash

OPTIONS="Shutdown\nReboot\nSleep\nHibernate\nEnd Session"

SELECTED=$(echo -e "$OPTIONS" | dmenu -i -p "Power Options:")

if [ -n "$SELECTED" ]; then
  CONFIRM=$(echo -e "Yes\nNo" | dmenu -i -p "Are you sure you want to $SELECTED?")

  if [ "$CONFIRM" == "Yes" ]; then
    case "$SELECTED" in
      "Shutdown") shutdown now ;;
      "Reboot") reboot ;;
      "Sleep") systemctl suspend ;;
      "Hibernate") systemctl hibernate ;;
      "End Session") pkill X ;;
    esac
  fi
fi
