#define WINVER 0x10086
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>

const char * sysVars = "extern string NULL = \"\";\n"
                       "extern int CL_BIGWHITE = 11,CL_RED = 12,CL_PINK = 13,CL_YELLOW2 = 14,CL_WHITE2 = 15;\n"
                       "extern int CL_PURPLE = 5,CL_ORANGE = 6,CL_WHITE = 7,CL_GREY = 8,CL_BLUE = 9,CL_YELLOW = 10;\n"
                       "extern int CL_BLACK = 0,CL_BLUE2 = 1,CL_GREEN = 2,CL_LIGHTBLUE = 3,CL_BIGRED = 4;\n";
const char * readMe = "请不要修改系统数据！\nPlease do not change the system data!\n";

int main(){
    _mkdir("C:\\ProgramData");
    _mkdir("C:\\ProgramData\\Ce");
    _mkdir("C:\\ProgramData\\Ce\\system");
    _mkdir("C:\\ProgramData\\Ce\\system\\headers");
    FILE * f = fopen("C:\\ProgramData\\Ce\\system\\headers\\sysVars.rb","w");
    fprintf(f,"%s",sysVars);
    fclose(f);
    f = fopen("C:\\ProgramData\\Ce\\README.MD","w");
    fprintf(f,"%s",readMe);
    fclose(f);
    MessageBox(NULL,"install successful!","installer",MB_OK);
    MessageBox(NULL,"The files are in C:\\ProgramData\\Ce","installeb",MB_OK);
 0  return 0;
}
