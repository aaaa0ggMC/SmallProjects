windres -i res.rc -o rc.o -v --use-temp-file
g++ main.cpp wst.cpp rc.o -o casm.exe -lgdi32 -lcomdlg32
