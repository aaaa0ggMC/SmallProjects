#ifndef WST_H_INCLUDED
#define WST_H_INCLUDED

#include <windows.h>
#include <stdlib.h>

void AssertE(LPCSTR l, HWND h);

void EAQ(int i, LPCSTR l, HWND h);
void EAQ(int i, LPCSTR l);
void EAQ(LPCSTR l);
int Q(LPCSTR l, HWND h);

#define E0 AssertE
#define E(l) AssertE(l,NULL)

#endif // WST_H_INCLUDED