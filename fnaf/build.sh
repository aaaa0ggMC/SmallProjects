windres -i rc.rc -o rc.o -v --use-temp-file
g++ main.cpp winMusicPlayer.cpp rc.o -o fnaf.exe -lsfml-graphics -lsfml-window -lsfml-system -lwinmm
