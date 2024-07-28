~/Scripts/wallLoop.sh A &
# inverts touchpad scroll, enables touch to click, and fixes my silly keyboard layout
~/Scripts/keybFix.sh &
picom --config ~/.config/picom/picom.conf &
xbindkeys &
redshift -P -O 4200 &
sudo light -S 3 &
dwmbar &
exec dwm 
