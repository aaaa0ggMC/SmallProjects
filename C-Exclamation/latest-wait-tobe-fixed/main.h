/**************************************************************************
Copyright:aaaa0ggMC
Author:aaaa0ggMC
Date:2020-08-17
Description:main.cpp Í·ÎÄ¼ş,ÉùÃ÷ÁËº¯Êı£¬Àà
**************************************************************************/
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#define _GLIBCXX_USE_CXX11_ABI 0
#define WINVER 0x10086
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <GL/gl.h>
#include <windows.h>
#include <ctype.h>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <vector>
#include <stdint.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include "ctool.h"

using namespace std;

#define delay Sleep(500)

#define Version "alpha 0.0.8.1.6 in home :) (Finally_Step1)"
#define UpdateTime "2021/02/01 - 2021/08/24"
#define StartTime  "2020/08/17"
#define programName "ce"


typedef void (*DefaultDLLFunc)(void);

typedef unsigned int ID;
typedef int errType;
typedef unsigned int CeType;
bool edit = false;

int defaultSW = 0;//findAllSW stgµÄÄ¬ÈÏ²ÎÊı

//IFID -- ¸øÃ¿¸öceÖĞifÓï¾äµÄÎ¨Ò»µÄID,»¹°üº¬ÊÇ·ñÖ´ĞĞ³É¹¦µÄĞÅÏ¢
struct IFID{
public:
    ID id;//ifÓï¾äµÄid
    static ID maxID;//idµÄ×î´ó´óĞ¡
    /*
    *Summary:·ÖÅäĞÂµÄÇÒÎ¨Ò»µÄid
    *Parameters:ÎŞ
    *Return : ²úÉúµÄID
    */
    ID NewId();
    /*
    *Summary:¹¹Ôì·½·¨£¬²úÉúID
    *Parameters:ÎŞ
    *Return :ÎŞ
    */
    IFID();
    /*
    *Summary:¹¹Ôì·½·¨£¬²úÉúID£¬²¢»ñÈ¡½á¹û
    *Parameters:
    *   result_:¸øµÄifÓï¾äµÄÔËĞĞ½á¹û
    *Return :ÎŞ
    */
    IFID(bool result_);
    boo, result;//ÔËĞĞ½á¹û£¬ÓÃÓÚ¼ì²âelseºÍelse ifÓï¾ä
    /*
    *Summary:»ñÈ¡ifµÄid
    *Parameters:ÎŞ
    *Return :¹«¹²³ÉÔ±±äÁ¿id
    */
    ID getId();
};
ID IFID::maxID = 0;//³õÊ¼»¯×î´óidÖµ

//PSStateID -- If Óï¾äµÄ¶ÀÌØid£¬ÎŞÅÅĞò
struct PSStateID{
    string condition;
    string0inside;
    PSStateID(string con,string in);
};

//PublicPair -- ¸üÍ¨ÓÃµÄID
template<class T> struct PublicID{
    T & first;
    T & second;
};

//CeVariable -- CeµÄ±äÁ¿
struct CeVariable{
public:
    string name;//±äÁ¿µÄÃû×Ö
    string value;//±äÁ¿µÄÖµ
    int depth;//×÷ÓÃÓòÇøÓò
    bool isconst;//±äÁ¿ÊÇ²»ÊÇconstµÄ
    bool inorecase;//´óĞ¡Ğ´
    bool out;//Êä³ö
    CeType type;
    /*
    *Summary:¹¹Ôìº¯Êı£¬ÓÃÓÚÉú³É±äÁ¿
    *Parameters:
    *   vname:±äÁ¿µÄÃû×Ö
    *   vvalue:±äÁ¿µÄÖµ
    *   const_:±äÁ¿ÊÇ·ñÊÇÖ»¶Á±äÁ¿
    *Return :ÎŞ
    */
    CeVariable(string vname,string vvalue,bool const_ = false,int depth_ = 0,bool _inorecase = false);
    /*
    *Summary:ÉèÖÃ±äÁ¿µÄÖµ
    *Parameters:
    *   v:±äÁ¿µÄÖµ
    *Return :·µ»ØÒ»¸öintÀàĞÍµÄÖµ(6»ò0),6Îª¸Ã±äÁ¿ÊÇconst±äÁ¿£¬²»¿ÉĞŞ¸Ä£¬0±íÊ¾Ã»ÓĞÒì³£
    *        µ«ÊÇÈç¹û¸³¸øÒ»¸öconst±äÁ¿ÏàÍ¬µÄÖµ£¬²¢²»»á±¨´í
    */
    errType setValue(string v,bool api = false);
};

//CeMemory -- ÏµÍ³ÄÚ´æ
struct CeMemory{
public:
    vector<CeVariable> mem;//ÄÚ´æ
    /*
    *Summary:¹¹Ôì·½·¨£¬ÓÃÓÚ³õÊ¼»¯ÄÚ´æ
    *Parameters:ÎŞ
    *Return :ÎŞ
    */
    CeMemory();
    /*
    *Summary:¼ì²âÄÚ´æÖĞÊÇ·ñÓĞÒ»¸ö±äÁ¿½Ğvname
    *Parameters:
    *   vname:´ı¼ì²â±äÁ¿µÄÃû×Ö
    *Return :
    *   ²¼¶ûÀàĞÍÖµ£¬·µ»ØÄÚ´æÖĞÊÇ·ñÓĞ¸Ã±äÁ¿£¬ÓĞ·µ»Øtrue,ÎŞ·µ»Øfalse
    */
    bool has(string & vname);
    /*
    *Summary:»ñÈ¡±äÁ¿ÔÚÄÚ´æ¿Õ¼äµÄÎ»ÖÃ
    *Parameters:
    *   vname:´ı»ñÈ¡ÖµµÄ±äÁ¿µÄÃû×Ö
    *Return :
    *   ·µ»ØÎ»ÖÃ£¬Èç¹û·µ»Ø-1£¬Ôò±íÊ¾Ã»ÓĞÕâ¸ö±äÁ¿
    */
    int getIndex(string & vname);
};

//Pos -- Position(Î»ÖÃ)
//C·ç¸ñ
struct Pos{
    int st;//¿ªÊ¼Î»ÖÃ
    int ed;//½áÊøÎ»ÖÃ
};

//BlockData -- ¿éĞÅÏ¢
//C·ç¸ñ
struct BlockData{
    string head;//Í·²¿
    string inside;//ÄÚÈİ
    char operators[3];//·ûºÅ
    /*
    *Summary:³õÊ¼»¯ÄÚÈİ
    *Parameters:ÎŞ
    *Return :ÎŞ
    */
    void init();
};

//ProgramInfo -- ÏîÄ¿ĞÅÏ¢(ÔÚ.ceÖĞ¿ÉÒÔµ÷ÓÃ)
//C·ç¸ñ
struct ProgramInfo{
    string fileLocation;//ÎÄ¼şÎ»ÖÃ
    string authorName;//×÷ÕßÃû×Ö
    unsigned long runTime;//ÏÖÔÚµÄÔËĞĞÊ±¼ä
};

typedef vector<PSStateID> TIfStates;
map<string,HMODULE> loadDlls;
int dllReleasedWhenRuntime = 0;
typedef TIfStates * PTIfStates;

vector<string> filer;//ÎÄ¼şÄÚÈİ
const string spector = "--------------------------------------------";//·Ö½çÏß
bool isBreak = false;//ÊÇ·ñÓÃÁËbreak;Óï¾ä
bool finalDebugMode = false;
int ifdepth = 0;//ifÓï¾äµÄÉî¶È
const errType varNotFound = 1,syntax = 2,isNotFunction = 3,oppCharNotHave = 4,/*noelse_if = 5,*/none = 0,constCannotSet = 6,
argNotEnough = 7,varReDefine = 8,varNotGood = 9,noAcess = 10,argNotGood = 11,programDefined = 12;
//¸÷ÖÖ´íÎóÀàĞÍ
/*
*varNotFound:Ã»ÓĞÕÒµ½±äÁ¿
*syntax:Óï·¨´íÎó
*isNotFunction:²»ÊÇº¯Êı
*oppCharNotHave:Ã»ÓĞÏàÓ¦µÄ×ªÒå×Ö·û
*noelse_if:ifdepthµÈÓÚ0,±íÊ¾Ã»ÓĞÏàÓ¦µÄifÓï¾ä,ÏÖÓĞelse(»òelse if)£¬´íÎó,ĞŞ¸Ä³ÉÁËºöÂÔ´íÎóµÄ¿éÓï¾äÍ·
*none:ÎŞ´íÎó
*constCannotSet:ÎŞ·¨ÉèÖÃconst±äÁ¿µÄÖµ
*/
vector<string> blocks{"if","loop","rloop","while","cmath"};//¿éÓï¾äµÄ±êÊ¶
string constVar = "$%Const^%",externVar = "$%Extern^%",ifselVar = "$system$selectIF^%~",apiVar = "$api$useAPI^%~",
apiIVar = "$api$inoreCase^%~",apiOutVar = "$api$outable^%~";
int maxDepth = 0;
bool nosee = false;
vector<unsigned int> warings;
ProgramInfo info;
CONSOLE_SCREEN_BUFFER_INFO consoleinfoin,consoleinfoo,consoleinfoe;
bool checkApi = true;WORD in;

string pdStr = "+ -({;";//ÅĞ¶¨µÄ×Ö·û´®

const WORD white = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
     0      red = FOREGROUND_INTENSITY|FOREGROUND_RED,green = FOREGROUND_INTENSITY|FOREGROUND_GREEN,
            blue = FOREGROUND_INTENSITY|FOREGROUND_BLUE,yellow = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN,
            pink = FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE,bigGreen /*ÇàÉ«*/= FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE,
            orign = FOREGROUND_INTENSITY,backwhite = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,
            backred = BACKGROUND_INTENSITY | BACKGROUND_RED,backgreen = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
            backblue = BACKGROUND_BLUE | BACKGROUND_INTENSITY,backyellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
            backpink = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,backBigGreen = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
            backorign = BACKGROUND_INTENSITY;//ÑÕÉ«
map<string,CeType> types{std::make_pair("TP_int",0),std::make_pair("TP_string",1)
                          ,std::make_pair("TP_var",2),std::make_pair("TP_float",3)};

/*
*Summary:½âÂë£¬Ê¶±ğ´úÂë
*Parameters:
*   file:ÎÄ¼şÄÚÈİ
*Return :ÎŞ
*/
void decode(vector<string> & file);
/*
*Summary:È¥³ıÇ°ºóµ¼¿Õ°××Ö·û£¬ÒÔ¼°'\0'
*Parameters:
*   str:´ı´¦ÀíµÄ×Ö·û´®
*Return :str
*/
string Trim(string & str);
/*
*Summary:ÇĞ¸î×Ö·û´®³É¶à¸öĞ¡×Ö·û´®
*Parameters:
*   vct:´ıĞ´ÈëµÄÈİÆ÷
*   line:Ä¿±ê
*   sep:ÇĞ¸îµÄ×Ö·û
*Return :ÎŞ
*/
void split(vector<string> & vct,const string & line,const char sep);
/*
*Summary:²âÊÔÊ±ÓÃÀ´°Ñ¿Õ°××Ö·û´òÓ¡³öÀ´
*Parameters:
*   str:´ı´òÓ¡µÄ×Ö·û´®
*Return :ÎŞ
*/
void DebugPrint(string str);
/*
*Summary:´¦Àí´íÎó
*Parameters:
*   type:¶¨Î»´íÎóµÄÀàĞÍ
*   line:¶¨Î»¼ì²éµ½ÎÄ¼şµÄĞĞÊı
*   character:¶¨Î»¼ì²éÎÄ¼şµÄµÚ¼¸¸ö×Ö·û
*   add:¸½¼Ó×Ö·û´®
*Return :ÎŞ
*/
void errMessage(errType type,int line,int character,string add);
/*
*Summary:´¦Àí´íÎó
*Parameters:
*   type:¶¨Î»´íÎóµÄÀàĞÍ
*   line:¶¨Î»¼ì²éµ½ÎÄ¼şµÄĞĞÊı
*   character:¶¨Î»¼ì²éÎÄ¼şµÄµÚ¼¸¸ö×Ö·û
*Return :ÎŞ
*/
void errMessage(errType type,int line,int character);
/*
*Summary:¼ì²é×Ö·û´®ÖĞÊÇ·ñ°üº¬ÁËÄ³¸ö×Ö·û
*Parameters:
*   c:×Ö·û
*   tar:´ı¼ì²â×Ö·û´®
*Return :²¼¶ûÀàĞÍ£¬Èç¹û°üº¬£¬·µ»Øtrue,·ñÔò·µ»Øfalse
*/
bool strInclude(char c,const string & tar);
/*
*Summary:²éÕÒ×Ö·û´®ÖĞÊÇ·ñÓĞÁíÒ»¸ö×Ö·û´®,µ«Èç¹ûÓëµ½'\"'£¬Ôò»áÌøÖÁÏÂÒ»¸ö'\"'£¬²¢¼ÌĞø¼ì²é
*Parameters:
*   tar:´ı²éÕÒ×Ö·û´®
*   cmp:²éÕÒµÄ×Ö·û´®
*   times:³öÏÖµÄ´ÎÊı
*Return :·µ»Ø²éÕÒµ½µÄÎ»ÖÃ£¬µ±²éÕÒ²»µ½Ê±£¬·µ»Ø-1»ò-2
*/
int find(const string & tar,const string & cmp,int times);
/*
*Summary:Ô¤´¦ÀíÎÄ¼ş£¬Ä¿Ç°Ö»É¾³ı×¢ÊÍºÍÔÚ¿éÓï¾äµÄ½áÎ²¶à¼ÓÒ»¸ö'\n'(·Ç³£ÖØÒª£¡)
*Parameters:
*   in:´ıĞ´ÈëÈİÆ÷
*   file:´ı¶ÁÈ¡ÈİÆ÷
*Return :ÎŞ
*/
void beforeRun(vector<string> & in,vector<string> & file);
/*
*Summary:µ¥´¿µÄ»ñÈ¡×Ö·û´®ÖĞÄ³¸ö×Ö·û³öÏÖµÄ´ÎÊı
*Parameters:
*   tar:´ı¶ÁÈ¡×Ö·û´®
*   c:×Ö·û
*Return :·µ»Ø³öÏÖµÄ´ÎÊı
*/
int getCharC(const string & tar,char c);
/*
*Summary:»ñÈ¡×Ö·û´®ÖĞÄ³¸ö×Ö·û³öÏÖµÄ´ÎÊı£¬µ«Èç¹ûÓëµ½'\"'£¬Ôò»áÌøÖÁÏÂÒ»¸ö'\"'£¬²¢¼ÌĞø¼ì²é
*Parameters:
*   tar:´ı¶ÁÈ¡×Ö·û´®
*   c:×Ö·û
*Return :·µ»Ø³öÏÖµÄ´ÎÊı
*/
int ceGetCharC(const string & tar,char c);
/*
*Summary:ºÍstring.find_last_of×÷ÓÃ¼¸ºõÒ»Ä£Ò»Ñù£¬×Ô¼ºÆ·
*/
size_t findLastIndexOf(const string & str,const string & compare);
/*
*Summary:²éÕÒÒ»¶ÔĞ¡À¨ºÅ¿éÄÚµÄÄÚÈİ
*Parameters:
*   tar:´ı¶ÁÈ¡×Ö·û´®
*   times:´ÎÊı
*Return :Î»ÖÃ
*/
Pos block_find_samllK(const string & tar,int times);
/*
*Summary:²éÕÒÒ»¶Ô´óÀ¨ºÅ¿éÄÚµÄÄÚÈİ
*Parameters:
*   tar:´ı¶ÁÈ¡×Ö·û´®
*   times:´ÎÊı
*Return :Î»ÖÃ
*/
Pos block_find_bigK(const string & tar,int times);
/*
*Summary:½«×Ö·û´®ÖĞµÄÊı¾İ½âÎö³öÀ´£¬²¢Ğ´ÈëÁíÒ»¸ö×Ö·û´®
*Parameters:
*   in:´ıĞ´Èë×Ö·û´®
*   tar:´ı¶ÁÈ¡×Ö·û´®
*   line:Ö´ĞĞµ½µÄĞĞÊı£¨ÓÉdecodeµÄ¼ÆÊıÆ÷¸øÓè£©
*Return :·µ»ØÊÇ·ñ¶ÁÈ¡³É¹¦£¬Èç¹û·µ»Ø²»ÊÇ"",ÄÇÃ´Ôò±íÊ¾²»´æÔÚÒ»¸ö±äÁ¿µÄÃû×Ö½Ğ£¨·µ»ØµÄÖµ£©
*/
string rsStr(string & in,const string & tar,int line = 0);
/*
*Summary:°ÑÎÄ¼şÖĞµÄ×Ö·û´®×ª»¯ÎªÊä³öµÄ×Ö·û´®£¬Èç"\\n"×ª³É"\n"...
*Parameters:
*   in:´ıĞ´Èë×Ö·û´®
*   str:´ı¶ÁÈ¡×Ö·û´®
*   rtV:½á¹û£¬µ±Ëü²»Îª-1Ê±£¬±íÊ¾Ê¶±ğ×ªÒå×Ö·û´íÎó
*Return :ÎŞ
*/
void toCeStr(string & in,string & str,int * rtV);
/*
*Summary:»ñÈ¡²¼¶ûÓï¾äµÄ½á¹û(Ö§³Ö&&,||)
*Parameters:
*   condition:Óï¾ä
*   errMsg:´íÎóµÄĞÅÏ¢£¬Èç¹ûËüÎª""£¬±íÊ¾Ã»ÓĞ´íÎó£¬·ñÔò±íÊ¾conditionÃ»ÓĞÒ»¸ö±äÁ¿½ĞerrMsg
*Return :½á¹û(Ò»°ã0»ò1)£¬µ«µ±Ëü·µ»Ø-1Ê±£¬±íÊ¾³öÎÊÌâÁË£¬ĞèÒª¼ì²âerrMsg
*/
int getConditionResult(string condition,string & errMsg);
/*
*Summary:»ñÈ¡²¼¶ûÓï¾äµÄ½á¹û
*Parameters:
*   condition:Óï¾ä
*   errMsg:´íÎóµÄĞÅÏ¢£¬Èç¹ûËüÎª""£¬±íÊ¾Ã»ÓĞ´íÎó£¬·ñÔò±íÊ¾conditionÃ»ÓĞÒ»¸ö±äÁ¿½ĞerrMsg
*Return :½á¹û(Ò»°ã0»ò1)£¬µ«µ±Ëü·µ»Ø-1Ê±£¬±íÊ¾³öÎÊÌâÁË£¬ĞèÒª¼ì²âerrMsg
*/
int getSMConditionResult(string condition,string & errMsg);
/*
*Summary:CeµÄºËĞÄÖ®Ò»£¬ÔËĞĞdecode()·Ö½â³öÀ´µÄĞ¡µÄ´úÂë(¿é)
*Parameters:
*   f:´ı½âÎö×Ö·û´®
*   line:ĞĞÊı
*   blockOpition:¸½¼ÓµÄĞÅÏ¢
*   ifStates:ÓÃÓÚ´¦ÀíifÓï¾äµÄ¸½¼ÓÏî
*Return :´¦ÀíÖµ
*/
CeVariable code(const string & f,int line,string blockOpition,PTIfStates ifStates = NULL,bool api = false,string varNameADD = "");
/*
*Summary:CeµÄºËĞÄÖ®Ò»£¬·Ö½â³öĞ¡µÄ´úÂë(¿é)
*Parameters:
*   file:Õû¸ö´óÎÄ¼ş
*Return :ÎŞ
*/
void decode(vector<string> & file);
/*
*Summary:×°ÔØÏµÍ³Ìá¹©µÄ.rb(CeÔ¤´¦Àí¹ıºóµÄÎÄ¼ş)ÎÄ¼ş£¬ÓÃÀ´¸¨ÖúÔËĞĞ
*Parameters:ÎŞ
*Return :ÎŞ
*/
void loadSystem();
/*
*Summary:×ª»¯×Ö·û´®ÎªÕûĞÍ±äÁ¿
*Parameters:
*   str:Ä¿±ê×Ö·û´®
*Return :×ª»¯µÄ½á¹û
*/
int toInt(std::string & str);
/*
*Summary:»ñµÃ±êÌâ
*Parameters:
*   line:¾ä×Ó
*   gv:¸½¼ÓËÑË÷
*Return :±êÌâ
*/
string getTitle(string line,string gv = pdStr);
/*
*Summary:»ñµÃ¿éµÄÄÚÈİ
*Parameters:
*   type:ÀàĞÍ,0±íÊ¾Ğ¡À¨ºÅ£¬1±íÊ¾´óÀ¨ºÅ
*   line:¾ä×Ó
*Return :½á¹û
*/
BlockData getBlockData(int type,string line);
/*
*Summary:Çå³ıÏàÓ¦×÷ÓÃÓòµÄ¿é
*Parameters:
*   mem:ÄÚ´æ¿Õ¼ä
*   depth:×÷ÓÃÓò²ãÊı
*Return :½á¹û
*/
void removeBlockVariable(CeMemory & mem,int depth);
/*
*Summary:²éÕÒÍêÕûµÄcmpÔÚ²»ÔÚtarÖĞ
*Parameters:
*   tar:Ä¿±ê
*   cmp:±È½Ï×Ö·û´®
*   times:³öÏÖ´ÎÊı
*   stg:»ñÈ¡¼ì²é¿ªÊ¼µÄ×Ö·û´®µÄÎ»ÖÃ
*Return :½á¹û
*/
string::size_type findAllSW(string tar,string cmp,int * stg = &defaultSW);
/*
*Summary:ÅÅĞò
*Parameters:
*   read:´ı¶ÁÈ¡Ä¿±ê
*Return :½á¹û
*/
template<class T> vector<T> sortVector(vector<T> read);
/*
*Summary:²éÕÒ×î´óÏî
*Parameters:
*   bg:´ı¶ÁÈ¡Ä¿±ê
*Return :½á¹û
*/
int findBiggest(vector<int> bg);
/*
*Summary:²éÕÒ×îÄÚ²¿µÄÀ¨ºÅÄÚµÄÏî
*Parameters:
*   tar:´ı¶ÁÈ¡Ä¿±ê
*Return :½á¹û
*/
Pos findInsidestC(string tar);
/*
*Summary:Ìæ»»str
*Parameters:
*   tar:´ı¶ÁÈ¡Ä¿±ê
*   token:Ä¿±ê
*   rp:Ìæ»»µÄ¶«Î÷
*Return :½á¹û
*/
string replaceStr(string tar,string token,string rp);
/*
*Summary:À©Õ¹stringµÄ¼Ó·¨
*Parameters:
*   ***
*Return :½á¹û
*/
string operator+(string a,string b);
string operator+(const char * a,string b);
string operator+(string b,const char * a);
/*
*Summary:´óĞ´
*Parameters:
*   ***
*Return :½á¹û
*/
string uppercase(string tar);
/*
*Summary:±àÒëÊ±ÔËĞĞÔ¤´¦Àí(±Ï¾¹:CeÊÇ½âÊÍĞÔÓïÑÔ)
*Parameters:
*   args:²ÎÊı
*Return :´íÎóÀàĞÍ
*/
errType use_pragma(vector<string> args);
/*
*Summary:Ê±¼ä
*Parameters:
*   args:²ÎÊı
*Return :ÎŞ
*/
void * timeable(void * arg);
/*
*Summary:windowsµÄÊÂ¼ş´¦Àí
*Parameters:
*   flags:ÑùÊ½
*Return :½á¹û
*/
BOOL loginCtrl(DWORD flags);
/*
*Summary:¼ì²âºöÂÔ¾¯¸æµÄid
*Parameters:
*   v:Öµ
*Return :½á¹û
*/
bool warsHas(unsigned int v);
/*
*Summary:¶à²ÊµÄ´òÓ¡Ò»´®ÎÄ×Ö
*Parameters:
*   meaage:ĞÅÏ¢
*   color:ÑÕÉ«
*Return :´òÓ¡µÄ×ÖÊı(printf·µ»Ø)
*/
int colorfulPrint(const string message,WORD color);
/*
*Summary:´òÓ¡Ò»´®ºìÉ«ÎÄ×Ö
*Parameters:
*   meaage:ĞÅÏ¢
*Return :´òÓ¡µÄ×ÖÊı(printf·µ»Ø)
*/
int errPrint(const string message);
/*
*Summary:´òÓ¡Ò»´®À¶É«ÎÄ×Ö
*Parameters:
*   meaage:ĞÅÏ¢
*Return :´òÓ¡µÄ×ÖÊı(printf·µ»Ø)
*/
int warPrint(const string message);
/*
*Summary:±äÁ¿µÄÃüÃû·¨Ôò
*Parameters:
*   meaage:ĞÅÏ¢
*Return :´íÎó
*/
errType varRule(string varName);
/*
*Summary:Ê¹ÓÃapi
*Parameters:
*   key:apiµÄÈ¨ÏŞ
*   funcName:º¯ÊıÃû
*   funcArgs:º¯ÊıµÄ²ÎÊı
*   return_:´¦ÀíÖµ
*Return :´íÎó
*/
errType apiUse(int key,string funcName,vector<string> funcArgs,string & return_);
/*
*Summary:ÅĞ¶ÏÊÇ·ñÊ¹ÓÃ¹ÜÀíÔ±ÔËĞĞ
*Parameters:ÎŞ
*Return :Öµ
*/
BOOL IsAdministrator(void);

void getArgs(std::string s,std::vector<std::string> args);

void UpdateDLL();

void CloseDLL();

//IOBUFFER -- ×Ô¼º¿ª·¢µÄÀà
struct IOBUFFER{
    static string input(char token,WORD color){
        char ch;
        string rt = "";
        while((ch = getch()) != token){
            if(ch == '\b')rt.resize(rt.length()-1);
            else rt += ch;
            colorfulPrint(string(&ch),color);
        }
        colorfulPrint(string(&token),color);
        return rt;
    }
};

namespace clink{
    typedef int(*TP_A)(void);
}

//Math Calculator
namespace mc{
    typedef long double Result;
    typedef std::string Input;

    struct ST_Pos{
        int st,ed;
    };

    struct ST_Mat0{
        Result a;
        int oper;//minus or add
    };

    Result cmath(Input in);

    Result clowLevelCal(vector<ST_Mat0> dta);

    Result chighLevelCal(Input in);

    Result ctoValue(Input in);
}

#endif // MAIN_H_INCLUDED
