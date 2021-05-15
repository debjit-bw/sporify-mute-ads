# Mute those ads

Whenever Spotify tries to play an ad, this mutes the system volume

---

## Conditions
Spotify needs to be present solely in a different window. You can open Spotify in a solo Chrome window where there's only this one tab, or you can use the desktop app.

---

## Installation
Normal g++ would do, but to link dlls statically,

    g++.exe -Wall -c -g mute_ads.cpp
    g++.exe -static -static-libgcc -static-libstdc++ -o "mute_ads.exe" mute_ads.o

I created a shortcut in my start menu with a cute icon, so you can do that, just fyi.

---

### Warning: 
Works only in Windows as it uses native system calls to determine which apps are running