# My Desktop 
![](images/screenshot-02-25.png)
`user` folder is equivalent to ~  

Basic stuff:

- Window manager: Dwm
- - The bar is out of the way, it shows up when mod is pressed
- Terminal: St
- App launcher: dmenu
- Compositor: picom

## Requirements in my .xinitrc
- Screen Temperature: redshift (my eyes hate blue)
- Brightness: light (my eyes hate bright)
- Wallpaper: hsetroot
- Keybinds: xbindkeys

some things also assume that you have

- mpd  
- xvkbd  

## Keybinds

Default dwm keybinds  
  
From .xbindkeysrc:  
Ctrl + Shift + t = St  
Ctrl + Shift + return = Dmenu (specifically dmenu_run)  
Ctrl + Shift + s = Power settings  
Ctrl + Shift + w = Wallpaper theme selector  
Ctrl + Shift + n = Paste using xvkbd  
Ctrl + Shift + m = set song menu  
Ctrl + Shift + k = set playlist menu  
Ctrl + Shift + F2 = screen recoding menu  

## Wallpapers

I have a folder in ~ called `Backgrounds`. In it, there are folders named with an id (such as A) which contains a set of images for the wallpaper rotation. In here theres only the files with the image Ids.   
The wallpaper theme selector ( Ctrl + Shift + w ) allows you to pick one.   
The themes must be manually set in `~/Scripts/wallBind.sh`   
A matching color chould also be set in `~/Scripts/generateColors.sh` which then creates a .xresources file to be read by dwm, though it only works on boot for now.   
Wallpaper rotates every 300 seconds.   

## Scripts

The scripts have comments at the top saying what they do.  
