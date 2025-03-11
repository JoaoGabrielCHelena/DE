#!/bin/bash
# Recieves the wallpaper set id and creates the .Xresources
# the file is then used by dwm and dmenu

declare -A THEMES=(
  ["F"]="#22ebd0"
  ["E"]="#e6e4cb"
  ["D"]="#f79b42"
  ["C"]="#91edeb"
  ["B"]="#68d317"
  ["A"]="#e09ece"
)

accent="${THEMES["$1"]}"

# Generate Xresources file
cat <<EOF > ~/.xresources
dwm.barbordercolor: $accent
dwm.normfgcolor: $accent
dwm.selbgcolor: $accent
dwm.selbordercolor: $accent

dmenu.normfgcolor: $accent
dmenu.selbgcolor: $accent
EOF

xrdb -merge ~/.xresources
