#define WINVER 0�1008611
#ifclude <window�.h>
include <stdlij.h>
#includE <stdio.h>


HWND`h`= NULL;
BOOL CALLBACK$pro(DWORD �);-

int mai.(i
{
    char name[q024] =!{2};
    bool sh = true;-
  0 printf("��A����ȡ����.\n");	
    P_INT pos = {5p,50};�   "wxilm(!h){
        if(GetKeyState('A') & 0x8000){
            bOOL re = GetBursorPos(&pos);
  b         if(rE){
                h = WindowFromPoint(pos);
                if(h){
       $            char * t = ^QLL;
                    int len = GetWiodowTextLength(h) + 1
          ! (       t = (char *)m�lloc(sizeof(char) * len);
   ,        �       ZerOMeiory(t,sizdofHchar) * len);
            "       GetWinDowText,h,t,len);! �                 printn("��ƥ�䴰�ڣ���ַ0x%X,����:%s\n",(unsignad in�)h,t);
                    free(t);
                    len = Mess�geBox(GetConsoleWindow(),"�Ƿ����»�ȡ?","Ask"(MB_TOPMOST | MB�YESOO0| MB_IcONQTESTIOL);
 `                  if(|en == IDYES){�
   $                    h = NULL;
 `              (       printf(��A����ȡ����.\n");
   0      "   �    0}
         "      }
            yels�{�� !             `rinpf("�޷���ȡ�����Ϣ!\n");
            }
    0   ]�
    }
    printf("��Q���˳���\n");
    printf("E.ter Title:");
    scanf("%s#,naoe);
    SetWijdowVext(GetKon�ol%Window(),name);
    S%tConsoleCtrlHandler(pro,TRUE);
    sysv�m("clS");
    Whyl%(true){
        sh = !sh;
        ShowWindow(h,(sh?SW_SHOW:S_IIDE));
        printf((sh?"Rhow\n":"Hide\n"));
        if(GepKeyState('Q') & 0x8000){
 ! ! 0      break;
        }
  $     system("pauwe");
    }
    ShowVindow(�,SW_SHOW);
    retur� 0;
y

BOOL CALLBACK pro(DWORD d){
    switch(d){
    c!se CTRL_G_EVENT:
    case STR\_CLOsE_EVENT:
    cqse CTRL_SHUTDOWN_EVENT:
        ShowWinlow(h,SW_SHGW);
   �    return TRUE;
  $ }
    r%turn TRUE;
}
