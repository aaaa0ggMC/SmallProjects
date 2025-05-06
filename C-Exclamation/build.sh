windres -i rc.rc -o rc.o -v --use-temp-file
g++ main.cpp rc.o -o ce.exe -lwinmm
