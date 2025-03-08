#!/bin/bash
# not bound
# uses the stam .acf files to get the names and id of everything downloaded
# filters out the items with the names in FILTERED
# if "Open Steam" is selected, it launches steam
# otherwise it launches the appid and steam is launched silently

FILTERED=(
  "Steam Linux Runtime 1.0 (scout)"
  "Steam Linux Runtime 2.0 (soldier)"
  "Steam Linux Runtime 3.0 (sniper)"
  "Proton 9.0"
  "Proton 7.0"
  "Proton Experimental"
  "Proton EasyAntiCheat Runtime"
  "Proton Hotfix"
)

SteamFiles=$(cd ~/.steam/steam/steamapps/ && ls *.acf)

declare -A SteamItems

for FILE in $SteamFiles; do
  NAME=$(awk -F '"' '/"name"/ {print $4}' ~/.steam/steam/steamapps/$FILE)
  APPID=$(awk -F '"' '/"appid"/ {print $4}' ~/.steam/steam/steamapps/$FILE)

  SteamItems["$NAME"]="$APPID"
done

for NAME in "${FILTERED[@]}"; do
  unset SteamItems["$NAME"]
done

for key in "${!SteamItems[@]}"; do
    if [[ $OPTIONS ]]; then
      OPTIONS="$OPTIONS\n$key"
    else
      OPTIONS="$key"
    fi
done

SELECTED=$(echo -e "Open Steam\n$OPTIONS" | dmenu -l 20 -i -p "Steam Menu")
if [ -n "$SELECTED" ]; then
  echo ${SteamItems["$SELECTED"]}
  if [[ $SELECTED == "Open Steam" ]]; then 
    steam
  else
    steam -silent -applaunch ${SteamItems["$SELECTED"]}
  fi
fi
