## Installation
Normal g++ would do, but to link dlls statically,

    g++.exe -Wall -c -g mute_ads.cpp
    g++.exe -static -static-libgcc -static-libstdc++ -o "mute_ads.exe" mute_ads.o

I created a shortcut in my start menu with a cute icon, so you can do that, just fyi.