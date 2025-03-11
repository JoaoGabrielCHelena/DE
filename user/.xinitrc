LETTER=$(echo $((RANDOM % 6 + 65)) | awk '{printf "%c", $1}')
~/Scripts/generateColors.sh "$LETTER"

~/Scripts/wallLoop.sh "$LETTER" &
# fixes my silly keyboard layout
~/Scripts/keybFix.sh &
picom --config ~/.config/picom/picom.conf &
redshift -P -O 4200 &
sudo light -S 3 &
dwmbar &
exec dwm 
