windres.exe -i Resource.rc -o rc.o -v --use-temp-file
g++ DesktopBack.cpp rc.o -o wallpaper.exe -lcomdlg32
