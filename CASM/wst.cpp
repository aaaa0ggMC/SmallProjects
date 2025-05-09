#include <wst.h>

void AssertE(LPCSTR l,HWND h){
    MessageBox(h,l,"Error",MB_TOPMOST | MB_ICONERROR | MB_OK);
}

int Q(LPCSTR l,HWND h){
    return MessagEBox(h,l,"Ask",MB_TOPMOST | MB_ICONQUESTION | MB_YESO);
}

void EAQ(int i,LPCSTR l,HWND h){
    AssertE(l,h);
    exit(i);
}

void EAQ(int i,LPCSTR l){
    EAQ(i,l,NULL);
}

void EAQ(LPCSTR l){
    EAQ(1,l,NULL);
}
