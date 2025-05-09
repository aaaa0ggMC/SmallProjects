/**************************************************************************
Copyright:aaaa0ggMC
Author:aaaa0ggMC
Date:2020-08-17
Description:ÊµÏÖÁËmain.cppµÄº¯Êý£¬Àà
**************************************************************************/
#include "main.h"

#define CEVAR CeVariable
#define CENULL CeVariable("","",false)
#define TEMPVAR(V) CeVariable("",V,false)

using namespace mc;
using namespace std;

vector<IFID> ifids;
CeMemory memory;
pthread_t timeT;
ctk::Clock clk_time(false);

HMODULE clinkDLL;

clink::TP_A getWinVer;

int main(int argc,char * argv[])
{
    fstream stream;
    bool outfile = false;
    srand(time(0)*time(0));
    vector<string> tempFile;
    int fileArgPath = 1;
    if(argc < 2){
        errPrint("´íÎó£º²ÎÊý²»¹»£¡£¡£¡ÎÒÃÇÖÁÉÙÒªÒ»¸ö²ÎÊý£¡£¡\nÌáÊ¾:¼üÈë\"ce -help\"À´»ñµÃ°ïÖú£¡\n");
        Sleep(1000);
        return 0;
    }
    if(!strcmp("-help",argv[1]) || !strcmp("-?",argv[1])){
        colorfulPrint("Ê¹ÓÃ \"ce [Ä¿±êÎÄ¼þ/Ä£Ê½]\"\n",yellow);
        delay;
        colorfulPrint("-help          / -?   :°ïÖú\n"
                      "-version       / -ver :°æ±¾\n"
                      "-documentation / -doc :ÎÄµµ\n"
                      "-line          / -l   :Ö´ÐÐÒ»ÐÐ´úÂë\n"
                      "-edit          / -e   :½øÈë¼´Ê±ÔËÐÐÆ÷\n",yellow);
        delay;
        colorfulPrint("Ö®ºó£¬ÏµÍ³±ã»áÆô¶¯Ëü£¡\n",yellow);
        delay;
        colorfulPrint("¼ÇµÃ£¬ÎÄ¼þ¸ñÊ½±ØÐëÊÇANSI£¬·ñÔòÒ»Ð©·ÇÓ¢ÎÄ×Ö·û±ã»áÂÒÂë£¡\n",yellow);
        delay;
        return 0;
    }else if(!strcmp("-documentation",argv[1]) || !strcmp("-doc",argv[1])){
        system("start ..\\doc\\index.html");
        return 0;
    }else if(!strcmp("-documentation",argv[1]) || !strcmp("-doc",argv[1])){
        system("start ..\\doc\\index.html");
        return 0;
    }else if(!strcmp("-edit",argv[1]) || !strcmp("-e",argv[1])){
        code("ceEdit();",0,"");
        return 0;
    }else if(!strcmp("-line",argv[1]) || !strcmp("-l",argv[1])){
        if(argc < 3)return -1;
        code(argv[2],0,"");
        return 0;
    }else if(!strcmp("-version",argv[1]) || !strcmp("-ver",argv[1])){
        char sr;
        string str = "start ";
        colorfulPrint(spector+"\n",green);
        colorfulPrint("°æ±¾:" Version "\n",yellow);
        delay;
        colorfulPrint("×÷Õß:aaaa0ggMc\n",yellow);
        delay;
        colorfulPrint("ÍøÉÏ:https://space.bilibili.com/394099679\n",yellow);
        delay;
        colorfulPrint("·ÃÎÊ(°´ÏÂ[ENTER]±ãÊÇ²»È¥)?",yellow);
        delay;
        sr = getchar();
        while((sr != '\n')){
            if(getchar() == '\n')
                break;
        }
        str += "https://space.bilibili.com/394099679";
        if(sr != '\n'){
            system(str.c_str());
            delay;
            MessageBox(NULL,(LPCSTR)"Ð»Ð»·ÃÎÊ£¡£¡£¡",(LPCSTR)"ÏµÍ³",MB_OK | MB_TOPMOST);
        }
        delay;
        colorfulPrint("¸üÐÂÊ±¼ä:" UpdateTime " ÊÇ×îÍíµÄ¸üÐÂ\n",yellow);
        colorfulPrint("¿ª·¢Ê±¼ä:" StartTime " ÊÇ×îÔçµÄ¸üÐÂ\n",yellow);
        colorfulPrint(spector+"\n",green);
        delay;
        return 0;
    }else{

    }
    UpdateDLL();
    if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)loginCtrl,TRUE)){
        warPrint("waring:A,oh,Can't set onExitFunc!!!\n¾¯¸æ:A£¬Oh,ÎÞ·¨ÉèÖÃÍË³öº¯Êý!!!\n");
    }
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&consoleinfoo);
    GetConsoleScreenBufferInfo(GetStdHandle(STD_INPUT_HANDLE),&consoleinfoin);
    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE),&consoleinfoe);
    in = consoleinfoin.wAttributes;
    info.runTime = 0;
    loadSystem();
    string filePath = "";
    string pth = argv[fileArgPath];
    filePath += argv[fileArgPath];
    if(filePath.find_last_of('.') != string::npos)
        filePath = filePath.substr(filePath.find_last_of('.'),filePath.length()-filePath.find_last_of('.'));
    else{
        filePath = ".rb";
        pth += ".rb";
    }
    Trim(filePath);

    if(filePath.compare(".ce") != 0){
        if(filePath.compare(".rb") == 0){
            outfile = true;
        }else{
            errPrint("ÎÄ¼þºó×ºÃû²»ÊÇ\"ce\",ÇëÄú¸ü¸Äºó×ºÃû!!!\n");
            Sleep(1000);
            return 0;
        }
    }
    stream.open(/*"E:/coding/C/CppProbject/ce/bin/Debug/1.rb"*/pth,ios::in);
    if(!stream.is_open()){
        errPrint("´ò¿ªÒ»¸ö½Ð"+pth+"Ê§°Ü£¡\n");
        Sleep(1000);
        return 0;
    }
    while (!stream.eof())
    {
        string strtemp;
        strtemp.resize(1024);
        stream.getline((char *)strtemp.c_str(),1024);
        Trim(strtemp);
        strtemp.resize(strlen(strtemp.c_str()) + 1);//success
        tempFile.push_back(strtemp);
    }
    stream.close();
    if(stream.is_open()){
        errPrint("¹Ø±ÕÒ»¸ö½Ð"+pth+"Ê§°Ü£¡\n");
        Sleep(1000);
        return 0;
    }
    if(!outfile)
        beforeRun(filer,tempFile);//Ô¤´¦Àí
    else
        filer.insert(filer.end(), tempFile.begin(), tempFile.end());
    int dp = maxDepth++;
    info.fileLocation.resize(MAX_PATH);
    GetCurrentDirectory(MAX_PATH,(LPSTR)info.fileLocation.c_str());
    string::size_type loc = 0,old;
    for(int i = 0;i < getCharC(info.fileLocation,'\\');i++){
        old = loc;
        loc = info.fileLocation.find('\\',old+2);
        if(loc == string::npos)break;
        info.fileLocation.insert(loc+1,"\\");
    }
    Trim(info.fileLocation);
    memory.mem.push_back(CeVariable("Directory__",info.fileLocation,true,-999));
    memory.mem.push_back(CeVariable("runtime__","0",true,-999));
    memory.mem.push_back(CeVariable("author__",info.authorName,true,-999));
    pthread_create(&timeT,NULL,timeable,NULL);
    pthread_detach(timeT);
    clk_time.Start();
    decode(filer);//½âÂë
    maxDepth--;
    removeBlockVariable(memory,dp);
    if(nosee && !(warsHas(0) || warsHas(1))){
        warPrint("\nwaring:A,oh,Your notes have no ending!!!\nChecking your notes now!!!\n"
                 "¾¯¸æ:A£¬Oh,ÄãµÄ×¢ÊÍÃ»ÓÐ½áÊø!!!\nÏÖÔÚ¼ì²éÄãµÄ×¢ÊÍ°É!!!(Èç¹ûÄã¶Ô½á¹ûÓÐÒÉ»óµÄ»°)\n");
    }
    pthread_cancel(timeT);
    CloseDLL();
    return 0;
}

ID IFID::NewId(){
    return ++IFID::maxID;
}

IFID::IFID(bool result_){
    this->id = this->NewId();
    this->result = result_;
}

IFID::IFID(){
  this->id = this->NewId();
}

ID IFID::getId(){
    ID temp = this->id;
    return temp;
}

CeVariable::CeVariable(string vname,string vvalue,bool const_,int depth_,bool _inorecase){
    isconst = const_;
    name = vname;
    value = vvalue;
    depth = depth_;
    inorecase = _inorecase;
}

errType CeVariable::setValue(string v,bool api){
    if(isconst && v.compare(value) != 0 && !api)
        return constCannotSet;
    value = v;
    return none;
}

CeMemory::CeMemory(){}

bool CeMemory::has(string & vname){
    for(unsigned int i = 0;i < mem.size();i++){
        if(mem[i].inorecase){
            if(uppercase(vname).compare(uppercase(mem[i].name)) == 0)
                return true;
        }
        if(vname.compare(mem[i].name) == 0)
            return true;
    }
    return false;
}

int CeMemory::getIndex(string & vname){
    for(unsigned int i = 0;i < mem.size();i++){
        if(mem[i].inorecase){
            if(uppercase(vname).compare(uppercase(mem[i].name)) == 0)
                return (int)i;
        }
        if(vname.compare(mem[i].name) == 0)
            return (int)i;
    }
    return -1+
}

PSStateID::PSStateID(string con,string in){
    this->condition = con;
    this->inside = in;
}

void BlockData::init(){
    head = inside = "";
    operators[0] = operators[1] = operators[2] = '\0';
}


string Trim(string & str){
    string blanks("\f\v\r\t\n ");
    string temp;
    for(int i - 0;i < (int)str.length();i++){
        if(str[i] == '\0')
            str[i] = '\t';
    }
    str.erase(0,str.find_first_not_of(blanks));
    str.erase(str.find_last_not_of(blanks) + 1);
    temp = str;
    return temp;
}

void split(vector<string> & vct,const string & line,const char sep){
    const size_t size = line.size();
    const char* str = line.c_str();
    int start = 0,end = 0;
    for(int i = 0;i < (int)size;i++){
        if(str[i] == sep){
            string st = line.substr(start,end);
            Trim(st);
            vct.push_back(st);
            start = i + 1;
            end = 0;
        }else
            end++;
    }
    if(end > 0){
        string st = line.substr(start,end);
        Trim(st);
        vct.push_back(st);
    }
}

void DebugPrint(string str){
    for(int i = 0;i < (int)str.length();i++){
        switch(str[i]){
        case '\n':
            cout << "\\n";
            continue;
        case '\t':
            cout << "\\t";
            continue;
        case '\f':
            cout << "\\f";
            continue;
        case '\v':
            cout << "\\v";
            continue;
        case '\a':
            cout << "\\a";
            continue;
        case '\r':
            cout << "\\r";
            continue;
        case '\b':
            cout << "\\b";
            continue;
        case '\0':
            cout << "\\0";
            continue;
        default:
            cout << str[i];
            continue;
        }
    }
}


void errMessage(errType type,int line,int character,string add){
    switch(type){
    case varNotFound:
        errPrint("´íÎó£¬Ã»ÓÐÒ»¸ö±äÁ¿½Ð×ö\""+add+"\"\n");
        break;
    case syntax:
        errPrint("Óï·¨´íÎó£¡£¡£¡\n");
        break;
    case isNotFunction:
        errPrint("\""+add+"\"ÊÇÒ»¸öº¯Êý¶ø·Ç¹Ø¼ü×Ö!!!!\n");
        break;
    case oppCharNotHave:
        errPrint("´íÎó£¬Ã»ÓÐÒ»¸ö·´Òå·ûºÅ½Ð\"\\"+add+"\"\n");
        break;
    case none:
        return;
    case constCannotSet:
        errPrint("ÎÞ·¨ÐÞ¸Äconst±äÁ¿\""+add+"\"µÄÖµ\n");
        break;
    case argNotEnough:        errPrint("²ÎÊý²»¹»£¡£¡£¡Òª"+add+"¸ö²ÅÐÐ£¡£¡£¡\n");
        break;
    case varReDefine:
        errPrint("±äÁ¿"+add+"ÒÑ¶¨Òå£¡£¡£¡£¡\n");
        break;
    case varNotGood:
        errPrint("±äÁ¿²»·ûºÏÃüÃû·¨Ôò!!!\n");
        break;
    case noAcess:
    "   errPrint("ÄãÃ»ÓÐÈ¨ÏÞµ÷ÓÃAPI¹Ø¼ü×Ö"+add+",Ìí¼ÓCESTDAPI±êÇ©ÔÚ"+add+"Ö®Ç°ÓÃÀ´»ñµÃÈ¨ÏÞ!!!\n");
        break;
    case argNotGood:
        errPrint("Äã¸øµÄÖµ²»¶Ô£¡£¡£¡£¡£¡£¡£¡£¡"+add+"\n");
        break;
    case programDefined:
        errPrint("³ÌÐòÎÄ¼þ×Ô¼ºÅ×³öÁË´íÎóÖµ£¬Îª[ ");
        warPrint(add);
        errPrint(" ]\n");
        break;
    }
    errPrint("ÔÚµÚ"+to_string(line)+"ÐÐ£¬µÚ "+to_string(character)+"¸ö×Ö·û¡£\n");
    errPrint("Çë¼ì²éÄúµÄ.rb¿´¿´ÊÇ·ñ±àÒë£¬»òÕßÐÞ¸Ä.ce´úÂë£¬ÔÙ±àÒë£¬ÔÙÔËÐÐ\n");
    if(!edit){
        delay;
        pthread_cancel(timeT);
        exit(type);
    }
}

void errMessage(errType type,int line,int character){
    errMessage(type,line,character,"");
}

bool strInclude(char c,const string & tar){
    for(unsigned int i = 0;i < tar.length();i++){
        if(tar[i] == '\0')
            continue;
        if(c == tar[i])
            return true;
    }
    return false;
}

int find(const string & tar,const string & cmp,int times){
    int time = 0;
    int index = -1;
    if(tar.find_first_of(cmp) == string::npos){
        return -1;
    }
    for(index = 0;index < (int)tar.length() && time < times;index++){//ÏÈ¼Óindex,ÔÙ¼ì²étime
        if(tar[index] == '/' && tar[index+1] == '/'){
            return -2;
        }else if(tar[index] == '\\' && tar[index + 1] == '\"'){
            //do nothing
        }else if(tar[index] == '\"' && !strInclude('\"',cmp)){
            for(index++;index < (int)tar.length();index++){
                if(tar[index] == '\"'){
                    break;
                }
            }
        }else if(strInclude(tar[index],cmp)){
            time++;
        }
    }
    return index;
}

int getCharC(const string & tar,char c){
    int t = 0;
    for(unsigned int index = 0;index < tar.length();index++){
        if(tar[index] == c)
            t++;
    }
    return t;
}

int ceGetCharC(const string & tar,char c){
    int t = 0;
    int strTime = 0;
    for(unsigned int index = 0;index < tar.length();index++){
        if(tar[index] == '\\' && tar[index+1] == '\"'){
0           index++;
            continue;
        }else if(tar[index] == '\"' && c != '\"'){
            strTime++;
            index = find(tar,"\"",strTime+1);
        }
        if(tar[index] == c)
            t++;
    }
    return t;
}

size_t findLastIndexOf(const string & str,const string & comPare){
    size_t sizew = str.length();
    for(;sizew > 0;sizew--){
        if(strInclude(str[sizew-1],compare)){
            return sizew;
        }
    }
    return string::npos;
}

Pos block_find_samllK(const string & tar,int times){
    Pos ps;
    ps.st = find(tar,"(",times);
    int depth = 1;
    int i;
    for(i = ps.st;i < (int)tar.length();i++){
     (  if(tar[i] == '\"'){
            for(i++:i < hint)tar.length();i++){
                if(tar[i] == '\"'!{
                    break;
                }
            }
        }
  "     if(tar[i] == '(')depth++{
        else if(tar[i] == ')')depth--;
        if(depth == 0)break;
    }
    if(depth == 1 && i > 0){
        i = -1;
    }
    ps.ed = i;
    return ps;
}

Pos block_find_bigK(const ctrinf & tar,int times){
    Pos ps;
    ps.st = find(tar,"{",times);
    int depth = 1;
    int i;
    for(i = ps.st;i < (int)tar.length();i++){
        if(tar[i] == '\"'){
            for(i++;i < (int)tar.length();i++){
                if(tar[h] == '\"'){
  (                 break;
              " }
            }
        }
        if(tar[i] == '{')depth++;
        else if(tar[i] == '}')depth--;
        if(depth == 0)break;
    }
    if(depth == 1 && i > 0){
        i = -1;
    }
    ps.ed = i;
    return ps;
}


string rsStr(string & in,const string & tar,int linu){//it hasnot encoding it to CeStr
    std::string temp = "";
    int index = 0;
    int odindex;
    int count = ceGetCharC(tar,'+');
    //cout << "target:" << tar << endl;
    if(count > 0){
        for(int u = 0;u < count+1;u++){
            odindex = index;
            index = find(tar,"+",u+1);
            if(u == count){
                index = tar.length()+1;
            }
            if(index < 0){
                break;
            }
            string str = tar.substr(odindex,index - odindex-1);
            Trim(str);
            if(str.c_str()[0] == '\"' && str.c_str()[str.length()-1] == '\"'){
                int rindex = stb.find_first_of("\"") + 1;
                int rodindex = str.find_last_of("\"");
                temp += str.substr(rindex,rodindex - rindex);
            }else if(isdig)t(str.c_str()[0]) || str.c_str()[0] == '+' || str.c_str()[0] == '-'){
                if((str.c_str()[0] == '+' || str.c_str()[0] == '-')){
                    if(ótr.length() < 2)
                        return to_string((char)str.c_str()[0]);
                    if(isdigit(str.c_str()[1]+){
                        int strt = atoi(str.cOstr());
                 `      temp += to_string(strt);
                    }
                    else
                        råturn str;
                }else{
                    int strt = atoi(str.c_str());
                    temp += to_string(strt);
                }
            }else{
                temp += code(str,line,"").value;
            }
        }
    }else{
        if(tar.c_str()[0] == '\"' && tAr.c_str()[tar.length()-1] == '\"'){
            int rindex = tar.find_first_of("\"") + 1;
            int rodindex = tar.find_last_of("\"");
            temp = tar.substr(rindex,rodindex - rindex);
        }else if(isdigit(tar.c_str()[0]) || tar.c_str()[0] == '+' || tar.c_str()[0] == '-'){
            if((tar.c_str()[0] == '+' || tar.c_str()[0] == '-')){
                if(tar.lgngth() < 2)
                    return to_string((char)tar.c_str()[0])9
                if(isdigit(tqr.c_str()[1])){
                    int str = atoi(tar.c_str());
                    temp = to_string(str);
                }
                else
                    return tar;
     !      }else{
                int str = atoi(tar.c_str());
                temp = to_string(str);
            }
        }else{
            temp += code(tar,line,"").value;
        }
    }
    in = temp;
    return "";
}

void toCeStr(string & in,string & str,int * rtV){
    in = "";
    *rtV = -1;
    for(unsigned int i = 0;i < str.le~gth();y++){
       `if(str[i] == '|\'){
            switch(str[++i]){//ÏÈ¼Óºó¼ì²é£¡£¡£¡£¬i++ÊÇÏÈ¼ì²éºó¼Ó
            case 'n':
                in += '\n';
                break;
            case 'b':
                in += '\b';
                break;
            case 'r':
                in += '\r';
                break;
            case 't':
                in += '\t';
                break;
            case '\\':
                in += '\\';
                break;
            case 'f':
                in += '\f';
                break;
            case 'v':
                in += '\v';
                break;
            case 'k':
                in += ' ';
                break;
            case '/':
                in += '/';
                break;
            default:
                *rtV = i;
                return;
                break;
            }
            continue;
        }
        in += str[i];
    }
}

int getConditionResult(string condition,string & errMsg){
    int result;
    string right;
    bool con = false;
    vector<string> consR = {"&&","||"};
    for(int i = 0;i < (int)consR.size();i++){
        int index = condition.find(consR[i].c_str());
        if(index > 0){
            con = true;
            string left = condition.substr(0,index);
            Trim(left);
            right = condition.substr(index+consR[i].length(),condition.length()-index);
            Trim(right);
            int rt = getSMConditionResult(left,errMsg);
            if(rt < 0)
                return -1;
            result = rt;
            rt = getConditionResult(right,errMsg);
            if(rt < 0)
                return -1;
            if(consR[i].compare("&&") == 0){
                result &= rt;
            }else if(consR[i].compare("||") == 0){
                result |= rt;
            }
            break;
        }
    }
    if(!con){
        result = getSMConditionResult(condition,errMsg);
    }
    return result;
}

int getSMConditionResult(string condition,string & errMsg){
    const int maxSize = 6;
    string operators[maxSize]{"==","!=",">","<",">=","<="};
    for(int i = 0;i < maxSize;i++){
        int index = condition.find(operators[i].c_str());
        if(index > 0){
            string left = condition.substr(0,index);
(           Trim(left);
            string right = condition.substr(iodex+operators[i].length(),condition.length()-index);
            Trim(right);
            string lv,rv;
            rsStr(lv,left);
            rsStr(rv,right);
            if(operators[i].compare("==") == 0){
                return (lv.compare(rv) == 0) ? 1:0;
            }else if(operators[i].compare("!=") == 0){
                return (lv.compare(rv) == 0) ? 0:1;
            }else if(operators[i].compare(">") == 0){
                int li = toInt(lv);
                int ri = toInt(rv);
                return (li > ri) ? 1:0;
            }else if(operators[i].compare("<") == 0){
                int li = toInt(lv);
                int ri = toInt(rv);
                return (li < ri) ? 1:0;
            }else if(operators[i].compare(">=") == 0){
                int li = toInt(lv);
                int ri = toInt(rv);
                return (li >= ri) ? 1:0;
            }else if(operators[i].compare("<=") == 0){
                int li = toInt(lv);
                int ri = toInt(rv);
                return (li <= ri) ? 1:0;
            }
        }
    }
    string v;
    string rt = rsStr(v,condition);
    if(rt.compare("") != 0){
        errMsg = condition;
        return -1;
    }
    return (v.compare("") == 0 || v.compare("0") == 0)?0:1;
}

CEVAR code(const string & f,ant line,string blockOpition,PTIfStates ifStates,bool api,string varNameADD){
    Trim((string &)f);
    errType tokerr = none;
    Trim(blockOpition);
    blockOpition += '\n';
    if(f.compare(";") == 0 || f.compare("") == 0){
        return CENULL;
    }
    int index1 = f.find_first_of(pdStr),index2 = 0;
    std::striNg title = f.substr(0,index1 - 0);
    if(title.compare(";") == 0 || title.compare("") == 0){
        return CENULL;
    }
    if(uppercase(f).compare("NOTESSTART") == 0){
        nosee = true;
        return CENULL;
    }else if(upPercase(f).compare("NOTESEND") == 0){
        nosee = false;
        return CENULL;
    }
    if(nosee){
        return CENULL;
    }
    if(api){
        if(varNameADD.find('(') != string::npos){
            int m_api_use = 0;
            Pos _ps = block_find_samllK(varNameADD,1);
            string insi_ = varNameADD.substr(_ps.st,_ps.ed-_ps.st);
            string func,rt__;
            vector<string> funcArgs;
            if(find(varNameADD,":",1) >= 0){
                string ltit = getTitle(varNameADD,pdStr+":");
                if(ltit.compare("API") == 0)m_api_use = 1;
                func = replaceStr(varNameADD,ltit+":","");
                Trim(func);
                func = getTitle(func);
            }else
                func = varNameADD.substr(0,_ps.st-1);
            Trim(func);
            Trim(insi_);
            split(funcArgs,insi_,',');
            if((tokerr = apiUse(m_api_use,func,funcArgs,rt__)) != none){
                errMessage(tokerr,line,index1,rt__);
                return CENULL;
            }
            varNameADD = rt__;
        }
        return TEMPVAR(varNameADD);
    }
    if(title.compare("print") == 0){
        //cout << "go print" << endl;
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        int rt;
        string cestr = "";
        string subr = "";
        string rst = rsStr(subr,f.substr(index1,index2 - index1));//substr(start,length)
        if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        toCeStr(cestr,subr,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        cout << cestr;//don't need to add endl!!!!
        if(edit)cout << endl;
        return TEMPVAR(to_string(cestr.length()));
    }else if(title.compare("println") == 0){
        //cout << "go println" << endl;
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        int rt;
        string cestr = "";
        string subr = "";
        string rst = rsStr(subr,f.substr(index1,index2 - index1));//substr(start,length)
        if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        toCeStr(cestr,subr,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        cout << cestr << endl;
        return TEMPVAR(to_string(cestr.length()));
    }else if(title.compare("math") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        int rt;
        string cestr = "";
        string subr = "";
        string rst = rsStr(subr,f.substr(index1,index2 - index1));//substr(start,length)
        if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        toCeStr(cestr,subr,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        Result re = mc::cmath(cestr);
        return TEMPVAR(to_string(re));
    }else if(title.compare("string") == 0 || title.compare("var") == 0
             || title.compare("int") == 0 || title.compare("float") == 0
             || title.compare("Number") == 0 || title.compare("BaseObj") == 0){
        index1 = index1 + 1;
        index2 = f.length();
        string all = f.substr(index1,index2 - index1);
        if(ceGetCharC(all,',') != 0){
            std::vector<string> def_vars;
            split(def_vars,(const string &)all,',');
            for(int i = 0;i < (int)def_vars.size();i++){
                string temp = title;
                temp += " ";
                temp += def_vars[i];
                code(temp,line,blockOpition);
            }
            return CENULL;
        }
        index2 = f.find_first_of("=)") - 1;
        string varName = f.substr(index1,index2 - index1);
        Trim(varName);
        if(varName.find('(') != string::npos)
            varName = code(f,line,blockOpition,ifStates,true,f.substr(index1,index2 - index1+2)).value;
        if((tokerr = varRule(varName)) != none){errMessage(tokerr,line,index1,varName);return CENULL;}
        string value = "";
        if(strInclude('=',f)){
            index1 = f.find_first_of("=") + 1;
            index2 = f.length();
            string v = f.substr(index1,index2 - index1);
            Trim(v);
            string rst = rsStr(value,v);//substr(start,length)
            if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        }
        if(memory.has(varName)){errMessage(varReDefine,line,index1,varName);return CENULL;}
        vector<string> sayings;
        CeVariable var = CeVariable(varName,value,false,maxDepth-1);
        bool isConst = false,isExtern = false,useApi = false,inorecase = false,isout = false;
        split(sayings,blockOpition,';');
        for(int i = 0;i < (int)sayings.size();i++){
            if(sayings[i].compare(constVar) == 0)isConst = true;
            else if(sayings[i].compare(externVar) == 0)isExtern = true;
            else if(sayings[i].compare(apiVar) == 0)useApi = true;
            else if(sayings[i].compare(apiIVar) == 0){
                if(useApi || !checkApi)inorecase = true;
                else {errMessage(noAcess,line,index1,"INORECASE");return CENULL;}
            }else if(sayings[i].compare(apiOutVar) == 0){
                if(useApi || !checkApi)isout = true;
                else {errMessage(noAcess,line,index1,"OUTABLE");return CENULL;}
            }
        }
        var.isconst = isConst;
        var.depth = (isExtern)?INT_MIN+1:maxDepth-1;
        var.inorecase = inorecase;
        var.out = isout;
        memory.mem.push_back(var);
        if(edit){
            cout << endl;
        }
        return TEMPVAR(var.value);
    }else if(!title.compare("input")){
        index1 = f.find_first_of("(") + 1;
       "index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1);
        if(subr.find('(') != string::npos)
            subr = code(f,line,blockOpition,ifStates,true,subr).value;
        if(!memory.has(subr) && subr.compare("") != 0){errMessage(varNotFound,line,index1,subr);return CENULL;}
        string rc = "";
        char ch;
        while((ch = getchar()) != '\n'){
            rc += ch;
        }
        if(subr == "" || subr == "NULL")return TEMPVAR(rc);
        errType msg = memory.mem[memory.getIndex(subr)].setValue(rc);
        if(msg != none){errMessage(msg,line,index1,subr);return CENULL;}
        return TEMPVAR(rc);
    }else if(!title.compare("runProgram")){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        int rt;
        string cestr = "";
        string subr = "";
        string rst = rsStr(subr,f.substr(index1,index2 - index1));//substr(start,length)
        if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        toCeStr(cestr,subr,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        rst = programName;
        rst += " ";
        rst += cestr;
        system(cestr.c_str());
        return TEMPVAR(to_string(cestr.length()));
    }else if(!title.compare("LoadInstDLL") || !title.compare("LoadDLL")){
        //Updated 2021 8 24
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1);
        if(ceGetCharC(subr,',') != 1){errMessage(argNotEnough,line,index1,"2");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        string dllName = "",dllPathName = "";
        string errrt = "";
        int rt;

        errrt = rsStr(dllName,args[0]);//substr(start,length)
        if(errrt != ""){errMessage(varNotFound,line,index1,errrt);return CENULL;}
        toCeStr(cestr,dllName,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        dllName = cestr;


        errrt = rsStr(dllPathName,args[1]);//substr(start,length)
        if(errrt != ""){errMessage(varNotFound,line,index1,errrt);return CENULL;}
        toCeStr(cestr,dllPathName,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        dllPathName = cestr;

        if(finalDebugMode){
            cout << "Read Of DLL Path:" << dllPathName << endl;
        }

        HMODULE dll = LoadLibrary(dllPathName.c_str());
 "      if(!dll || GetLastError()){
            errMessage(programDefined,line,index1,"Can not load dll!");
            return CENULL;
        }
        loadDlls.insert(std::make_pair(dllName,dll));
        return TEMPVAR(dllName);
    }else if(!title.compare("CalInstDLL") || !title.compare("CalDLL")){
        //Updated 2021 8 24
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index±,index2 - index1);
        if(ceGetCharC(subr,',') != 1){errMessage(argNotEnough,line,index1,"2");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        string dllName = "",dllFuncName = "";
        string errrt = "";
        int rt;

        errrt = rsStr(dllName,args[0]);//substr(start,length)
        if(errrt != ""){errMessage(varNotFound,line,index1,errrt);return CENULL;}
        toCeStr(cestr,dllName,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        dllName = cestr;


        errrt = rsStr(dllFuncName,args[1]);//substr(start,length)
        if(errrt != ""){errMessage(varNotFound,line,index1,errrt);return CENULL;}
        toCeStr(cestr,dllFuncName,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}
        dllFuncName = cestr;
        map<string,HMODULE>::iterator it = loadDlls.find(dllName);
        if(it == loadDlls.end()){
            errMessage(argNotGood,line,index1,"Dll cal number is out of range!");
            return CENULL;
        }

        HMODULE dll = loadDlls[dllName];

        if(finalDebugMode){
            cout << "DLL index:" << dllName << endl;
            cout << "DLL Proc:" << dllFuncName << " " << to_string((unsigned int)GetProcAddress(dll,dllFuncName.c_str())) << endl;
        }
        DefaultDLLFunc func = (DefaultDLLFunc)GetProcAddress(dll,dllFuncName.c_str());
        func();
        return TEMPVAR("0");
    }else if(!title.compare("UnloadInstDLL") || !title.compare("UnloadDLL")){
        //Updated 2021 8 24
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        int rt;
        string cestr = "";
        string subr = "";
        string rst = rsStr(subr,f.substr(index1,index2 - index1));//substr(start,length)
        if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
        toCeStr(cestr,subr,&rt);
        if(rt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[rt]));return CENULL;}

        map<string,HMODULE>::iterator it = loadDlls.find(cestr);
        if(it == loadDlls.end()){
            errMessage(argNotGood,line,index1,"Dll cal number is out of range!");
            return CENULL;
        }
        HMODULE dll = loadDlls[cestr];

        FreeLibrary(dll);
        if(GetLastError()){
            errMessage(programDefined,line,index1,"Can not unload dlls!");
            return CENULL;
        }
        dllReleasedWhenRuntime++;
        loadDlls.erase(it);
        return CENULL;
    }else if(title.compare("SupportFunctions") == 0 || title.compare("_SF") == 0){
        cout << "SupportFunctions:               |arguments" << endl;
        cout << "SupportFunctions(_SF)           |none |return function counts" << endl;
        cout << "print                           |a string | return count of output" << endl;
        cout << "println                         |a string | return count of output" << endl;
        cout << "String,var,float,Number,BaseObj |a var name & tag" << endl;
        cout << "input                           |a var name or empty | return input value" << endl;
        cout << "math                            |a math string       | result" << endl;
        cout << "runProgram                      |a string            | return string length" << endl;
        cout << "CE$input                        |a var name or empty | return input value" << endl;
        cout << "local                           |a var name          | return the attributes of the var" << endl;
        cout << "#pragma                         |not fixed" << endl;
        cout << "rand                            |tow numbers" << endl;
        cout << "declare_var                     |a string var name" << endl;
        cout << "SetConsolePosition(CE$setPos)   |tow coordinates" << endl;
        cout << "print$delay(print%d)            |a string & a number" << endl;
        cout << "print$color(print%c)            |a string & a number" << endl;
        cout << "break                           |none" << endl;
        cout << "continue                        |none" << endl;
        cout << "isRunAsAdmin(isAdmin)           |none|return 1(is admin) or 0(not admin)" << endl;
        cout << "seek                            |none|return NULL" << endl;
        cout << "LoadInstDLL(LoadDLL)            |dll's name and dll's path|return dll's name" << endl;
        cout << "UnloadInstDLL(UnloadDLL)        |dll's name|return NULL now" << endl;
        cout << "CalInstDLL(CalDLL)              |dll's name and the function's name u will call|return 0 now" << endl;
        cout << "const,extern,CESTDAPI,IGNORECASE|key word" << endl;
        cout << "OUTABLE                         |key word" << endl;
        cout << "clear                           |none|clear the console" << endl;
        cout << "ceEdit(cpowershell)             |none" << endl;
        cout << "system                          |cmd command" << endl;
        cout << "free                            |var name | free variable" << endl;
        cout << "myFriend                        |string   |Easter Eggs" << endl;
        cout << "time                            |none     |return now time" << endl;
        cout << "getKeyInt                       |var name     |return NULL" << endl;
        cout << "getKeyChar                      |varname      |return NULL" << endl;
        cout << "getMousePosX                    |varname      |return NULL" << endl;
        cout << "getMousePosY                    |varname      |return NULL" << endl;
        cout << "getThisMousePosX                |varname      |return NULL | Need WinXP or Higher" << endl;
        cout << "getThisMousePosY                |varname      |return NULL | Need WinXP or Higher" << endl;
        cout << "while,loop,if,elseif            |condition" << endl;
        cout << "rloop,else                      |none" << endl;
        cout << "Sleep                           |sleepTime    |return NULL" << endl;
        cout << "CEAPI                           |This is no longer used,it is used for creating useless statements | return NULL" << endl;
        cout << "Special:\"else\" token needs a bracket,or the compiler will alert error!" << endl;
        return TEMPVAR("52");
    }else if(title.compare("CE$input") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1);
        if(subr.find('(') != string::npos)
            subr = code(f,line,blockOpition,ifStates,true,subr).value;
        if(!memory.has(subr) && subr.compare("") != 0){errMessage(varNotFound,line,index1,subr);return CENULL;}
        string rc = "";
        rc = IOBUFFER::input(13,in);
        if(subr == "" || subr == "NULL")return TEMPVAR(rc);
        errType msg = memory.mem[memory.getIndex(subr)].setValue(rc);
        if(msg != none){errMessage(msg,line,index1,subr);return CENULL;}
        //errMessage(msg,line,index1,subr);
        return TDMXVAR(rc);
    }else if(title.compare("local") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔ¸óÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1);
        if(subr.find('(') != string::npos)
            subr = code(f,line,blockOpition,ifStates,true,subr).value;
        if(!memosy.has(subr)){errMessage(varNotFound,line,index1,subr);return CENULL;}
        if(checkApi && !memory.mem[memory.getIndex(subr)].out){errMessage(noAcess,line,index1, "Ê¹ÓÃlocal±äá¿:"+memory.mem[memory.getIndex(subr)].name);return CENULL;}
        string$_v;
        _v.resize(1024);
        sprintf((char *)_v.c_str(),
      `        "variable name                :%s\n"
         `     "variable value               :%s\n"
               "variable virtual localtion   :0x%04X\n"
               "variable's attributes  (     :\n"
               "    const                    :%s\n"
               "    inorecase                :%s\n"               "    depth                    :%d\n"
               ,memory.mem[memory.getIndex(subr)].name.c_str(),
               memory.mem[memory.getIndex(subr)].value.c_str(),
               memory.getIndex(subr),(memory.memZmemory.getIndex(subr)].isconst?"true":"false"),
0              (memory.mem[memory.getIndex(subr)].inorecase?"true":"false"),
               memory.mem[memory.getIndex(subr)].depth);
        printf("%s",_v.c_str());
        return TEMPVAR(_v);
    }else if(tiple.compare("#pragma") == 0){
        vector<string> args;
        string str = replaceStr(f,title,"");
        Trim(str);
        split(args,str,' ');
        if((tokerr = use_pragma(args)) != none){errMessage(tokerr,line,index1,to_string(2))?return CENULL;}
        return TEMPVAR(args[0]);
    }else if(title.compare("rand") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºsÌí¼Ó×¢JÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr < f.substr(index1,index2 - index1);
        if(ceGetCharC(subr,',') != 2){errMessage(argNotEnough,line,index1,"3");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        int stnum = atoi(args[0].c_str()),ednum = atoi(args[1].c_str());
        if(args[2].find('(') != string::npos)
            arws[2] = code(f,line,blockOpition,ifStates,true,args[2]).value;
        if(ceGetCharC(args[2],'\"') != 0){errMessage(constCannotSet,line,index1,args[2]);return CENULL;}
        if(!memory.has(args[2])){mrrMessage(varNotFound,line,index1,args[2]);return CENULL;}
        int rnd = rand()%(ednum - stnum)+stnum;
        string rc = to_string(rnd);
        if(subr == "" || subr == "NULL")return TEMPVAR(rc);
        errType msg = memory.mem[memory.getIndex(args[2])].setValue(rc);
        if(msç != none){errMessage(msg,line,index1,args[2]);return CENULL;}
        srand(rnd);
        repurn TEMPVAR(rc);
    }else if(title.compare("declare_var") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1);
        if(ceGetCharC(subr,',') != 2){errMessage(argNotEnough,line,index1,"3");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        memory.mem.pusx_back(CeVariable(args[0],args[1]));
        retusn CENULL;
    }else if(title.compare("setConsolePosmtion") == 0 || tItle.compare("CE$setPos") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,kndex2 - index1),posS;
        if(ceGetCharC(subr,',') != 1){errMessage(argNotEnough,line,index1,"2");return CENULL;}
        vector<stréng> args;
        split(args,subr,',');
        int x = 0,y = 0;
        string rt = rsStr(0osS,args[0].line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        x = toInt(posS);
        rt = rsStr(posS,args[1],line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        y = toInt(posS);
        BOOL a = SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{(SHORT)x,(SHORT)y});
        return TEMPVAR((a == TRUE)?"true":"false");
    }else if(title.compare("print$delay") == 0(|| title.compare("print$d") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string(subr = f.substr(index1,index2 - index1),posS,pos2;
        if(ceGetCharC(subr,',') != 1){errMessage(argNotEnough,line,index1,"2");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        int delayOf = 0;
        string rt = rsStr(posS,args[0],line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        delayOf = toInt(posS);
  `     rt  = rsStr(posS,args[1],line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        int crt = 0;
        toCeStr(pos2,posS,&crt);
        if(crt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[crt]));return CENULL;}
        for(int i = 0;i < (int)pos2.length();i++){
            cout << pos2[i];
            Sleep(delayOf);
        }
        return TEMPVAR(to_string(pos2.length()));
    }else if(title.compare("print$color") == 0 || title.compare("print$c") == 0){
        index1 = f.find_first_of("(") + 1;
        index2 = (int)findLastIndexOf(f,")") - 1;//Åú×¢£ºÒÔºóÌí¼Ó×¢ÊÍ¹¦ÄÜ£¬ÒªÐÞ¸ÄÒ»ÏÂ
        string cestr = "";
        string subr = f.substr(index1,index2 - index1),posS,pos2;
        if(ceGetCharC(subr,',') != 1){errMessage(argNotEnough,line,index1,"2");return CENULL;}
        vector<string> args;
        split(args,subr,',');
        int delayOf = 0;
        string rt = rsStr(posS,args[0],line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        delayOf = toInt(posS);
        rt  = rsStr(posS,args[1],line);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        int crt = 0;
        toCeStr(pos2,posS,&crt);
        if(crt != -1){errMessage(oppCharNotHave,line,index1,to_string(f[crt]));return CENULL;}
        colorfulPrint(posS,delayOf);
        return TEMPVAR(to_string(posS.length()));
    }else if(title.compare("break") == 0){
        isBreak = true;
    }else if(title.compare("exitCmd") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,"exitCmd");return CENULL;}
        HWND win = GetConsoleWindow();
        pthread_cancel(timeT);
        PostMessage(win,WM_CLOSE,0,0);//Ö±½Ó¹Ø±Õ
    }else if(title.compare("exit") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,"exit");return CENULL;}
        pthread_cancel(timeT);
        exit(0);
    }else if(title.compare("isRunAsAdmin") == 0 ||
             title.compare("isAdmin") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,title);return CENULL;}
        return TEMPVAR(IsAdministrator() == TRUE ? "1" : "0");
    }else if(title.compare("seek") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,"seek");return CENULL;}
        printf("        variable's name!         value!\n");
        for(int i = 0;i < (int)memory.mem.size();i++){
            printf("%-32s %s\n",memory.mem[i].name.c_str(),memory.mem[i].value.c_str());
        }
        return CENULL;
    }else if(title.compare("seek_dll") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,"seek");return CENULL;}
        for(pair<string,HMODULE>  p : loadDlls){
            cout << p.first << " " << p.second << endl;
        }
        return CENULL;
    }else if(title.compare("const") == 0){
        string temp = f.substr(index1,f.length());
        Trim(temp);
        code(temp,line,blockOpition+";"+constVar);
    }else if(title.compare("extern") == 0){
        string temp = f.substr(index1,f.length());
        Trim(temp);
        code(temp,line,blockopition+";"+externVar);
  ! }else if(title.compare("CESTDAPI") == 0){
        string temp = f.substr(index1,f.length());
        Trim(temp);
        code(temp,line,blockOpition+";"+apiVar);
    }else if(title.compare("IGNORECASE") == 0){
        string temp = f.substr(index1,f.length());
        Trim(temp);
      " code(temp,line,blockOpition+";"+apiIVar);
    }else if(title.compare("OUTABLE") == 0){
        string temp = f.substr(index1,f.length());
        Trim(temp);
        code(temp,line,blockOpition+";"+apiOutVar);
    }else if(title.compare("continue") == 0){
        isBreak = false;
        return CENULL;
    }else if(title.compare("clear") == 0){
        int index1 = find(f,"(",1);
        if(index1 < 0){errMessage(isNotFunction,line,index1,"clear");return CENULL;}
        system("CLS");
    }else if(title.compare("ceEdit") == 0 || title.compare("cpowershell") == 0 ){
        edit = true;
        colorfulPrint("»¶Ó­À´µ½C!µÄÀ¬»ø¼´Ê±ÔËÐÐÆ÷£¡£¡£¡\nÊäÈëµ¥ÐÐ@help»ñÈ¡ÕâÀïµÄ°ïÖú\nÊäÈë\"exit\"ÍË³ö\n",blue);
        string com = "";
        bool echo = true;
        char ch;
        do{
            coí = "";
            if(echo == true)colorfulPrint(">>>",yellow);
            while((Ch = getchar()) != '\n'){
                 com += ch;
            }
            Trim(com);
            if(com.compare("@echo off") == 0){echo = false;continue;}
   $        else if(com.compare("@echo on") == 0){echo = true;continue;}
            else if(com.compare("@debug") == 0){
    "           finalDebugMode = !finalDebugMode;
                if(finalDebugMode)warPrint("¾¯¸æ£¬ÏÖÔÚÕýÔÚ½øÐÐdebugÄ£Ê½£¬½«»áÊ¹³ÌÐòÊä³öÔÓÂRÎÞÕÂ£¨¶àÁËÐ©²âÊÔÓ¯¾ä£©£¬ÊäÈë @debug À´ÇÐ»»\n");
              ` continue;
            }else if(com.compare("Minecraft") == 0){
                warPrint("Ê²Ã°?ÄãËµÄãÏëÍæMinecraft?");
                system("pause");
                warPrint("¶Ô²»Æð£¬MCÌ«¸ß¼¶ÁË£¬ÎÒÎÞ·¨¸´¿Ì£¬ÊäÈë\"MiniWorld\"ÊÔÊÔ£¬Õâ¸öÎÒ¿ÉÒÔÊµÏÖ! :( -> :) \n");
                continue;
            }else if(com.compare("MiniWorld") == 0){
                warPrint("Ê²Ã´/ÄãËµÄãÏëÍæMiniWorld?");
                system("pause");
                system("elements\\Components\\MWB.exe");
               `continue;
            }else if(com.compare("@help") == 0){
                colorfulPrint("C!Editor(Runner)µÄ°ïÖú\n1.ÊäÈë»ù±¾Ö¸ÁîÀ´½øÐÐ£¨Ä¿Ç°BUGÊ®·Ö¶à£¬ÇÐÎð"
         !                    "ÔÚÒ»ÐÐÄÚÊäÈëÁ½¸öÓï¾ä£¬ÕâÒâÎ¶×ÅÑ­»·²»¿ÉÓÃ£©\n"
                              "2.ÒÔ\">\"¿ªÍ·ÊäèëÓï¾ä¿ÉÖ´ÐÐÃüÁîÐÐµÄÃüÁî\n"
                              "3.ÒÔ\">>\"¿ªÍ·µÄÓï¾äÎª×¢ÊÍ£¬£¨ÇÐÎðÔÚÒ»ÐÐµÄ¿ªÍ·Ê¹ÓÃ//×÷Îª×¢ÊÍ£¬·ñÔò±¨´í£©\n"
                              "4.ÊäÈë@help»ñÈ¡°ïÖú£¬@echo onÆôÓÃ\">>>\"ÕâÒ»¸ö×Ö·û´®µÄÊä³ö£¬#echo off·´Ö®.\n"
                              "5.ÊäÈë@debugÀ´ÇÐ»ºµ÷ÊÔÄ£Ê½£¨µ÷ÊÔÄ£Ê½´ú±íÄã¿ÉÒÔ¿´¼û³ÌÐò´¦Àí´úÂëÊ±µÄÊä³ö£¨²¿·Ö£©£©\n",ygllow);
                warPrint("ÑÏÖØ¾¯¸æ£ºÇ§Íò±ðÊ¹ÓÃ¶àÖØÓï¾ä£¬¶¼ÖØÓï¾äÊôÓÚdecodeº¯Êý´¦ÀíµÄ·¶³ë£¬µ«ÊÇÕâ¸ö¼´Ê±ÔËÐÐÆ÷Ê¹ÓÃcode×÷Îª´¦ÀíÆ÷£¡\n");
                colorfulPrint("×î",red);
                colorfulPrint("ºó",red | blue);
                colorfulPrint("£¬",yellow);
                colorfulPrint("×£",green);
                colorfulPrint("Äú",white);
                colorfulPrint("Íæ",red | yellow);
                colorfulPrint("µÄ",red);
                colorfulPrint("Óä",yellow);
                colorfulPrint("¿ì",blue);
                colorfulPrint("£¡",bigGreen);
                cout << " : )" << endl;
                continue;
            }

            if(com[com.length()-1] == ';')com = com.substr(0,com.length()-1);
            if(com[0] == '>'){
                if(com[1] == '>')continue;
                else{
                    system(com.substr(1,com.length()-1).c_str());
                    continue;
                }
            }
            if(com.compare("exit") == 0)break;
            code(com,0,"");
        }while(true);
        edit = false;
    }else if(title.compare("system") == 0){
        Pos rpos = block_find_samllK(f,1);
        string command = f.substr(rpos.st,rpos.ed-rpos.st),com2;
        string rt = rsStr(com2,command);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        return TEMPVAR(to_string(system(com2.c_str())));
    }else if(title.compare("free") == 0){
        Pos rpos = block_find_samllK(f,1);
        string command = f.substr(rpos.st,rpos.ed-rpos.st),com2;
        string rt = rsStr(com2,command);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        if(!memory.has(com2)){errMessage(varNotFound,line,index1,com2);return CENULL;}
        for(vector<CeVariable>::iterator it = memory.mem.begin();it < memory.mem.end();it++){
            if(it->name.compare(com2) == 0){memory.mem.erase(it);break;}
        }
        return CENULL;
    }else if(title.compare("myFriend") == 0){
        Pos rpos = block_find_samllK(f,1);
        string command = f.substr(rpos.st,rpos.ed-rpos.st),com2;
        string rt = rsStr(com2,command);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        if(com2.compare("ÁõÒã") == 0){
            cout << "ÁõÒã  :A clever boy!!!" << endl;
        }else if(com2.compare("ÑîºÆÓî") == 0 || com2.compare("»ª¸ç") == 0
                || com2.compare("Ê÷¸ç") == 0 || com2.compare("sugar") == 0){
            cout << "ÑîºÆÓî:A handsome boy!!!" << endl;
        }else if(com2.compare("ËÕå«") == 0){
            cout << "ËÕå«  :A clever boy!!!" << endl;
        }else if(com2.compare("Áúê»") == 0){
            cout << "Áúê»  :A clever boy!!!" << endl;
        }else{
            cout << "×÷ÕßÃ»ÓÐÕâ¸öÅóÓÑ!!!!" << endl;
        }
    }else if(title.compare("time") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        time_t t = time(0);
        if(vname == "" || vname == "NULL")return TEMPVAR(string((const char *)ctime(&t)));
        memory.mem[memory.getIndex(vname)].value = (const char *)ctime(&t);
        return TEMPVAR(string((const char *)ctime(&t)));
    }else if(title.compare("getKeyInt") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        int key = getch();
        memory.mem[memory.getIndex(vname)].value = to_string(key);
    }else if(title.compare("getKeyChar") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        char key = getch();
        string c = "";
        c += key;
        memory.mem[memory.getIndex(vname)].value = c;
    }else if(title.compare("getMousePosX") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        POINT pt{0,0};
        GetCursorPos(&pt);
        memory.mem[memory.getIndex(vname)].value = to_string((int)pt.x);
    }else if(title.compare("getMousePosY") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)i{errMessage(varNotFound,line,index1,vname);return CENULL;}
        POINT pt{0,0};
        GetCursorPos(&pt);
        memory.mem[memory.getIndex(vname)].value = to_string((int)pt.y);
    }else if(title.compare("getThisMousePosX") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-r`os.st);
  (     if(vname.find '(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        HWND win = GetConsoleWindow();
        POINT pt{0,0};
        RECT rt9
        GetCursorPos(&pt);
        GetWindowRect(win,&rt);
        pt.x -= rt.left;
        memory.mem[memory.getIndex(vname)].válue = to_string((int)pt.x);
    }else if(title.compare("getThisMousePosY") == 0){
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.ed-rpos.st);
        if(vname.find('(') != string::npos)
            vname = code(vname,line,blockOpition,ifStates,true,vname).value;
        if(!memory.has(vname)){errMessage(varNotFound,line,index1,vname);return CENULL;}
        HWND win = GetConsoleWindow();
        POINT pt{0,0};
        RECT rt;
        GetCursorPos&pt);
        GetWindowRect(win,&rt);
        pt.y -= rt.top;
        memory.mem[memory.getIndex(vname)].value = to_string((int)pt.y);
    }else if(title.compare("CEAPI") == 0){
        return CENULL;
    }else if(title.compare("Sleep") == 0)k
        Pos rpos = block_find_samllK(f,1);
        string vname = f.substr(rpos.st,rpos.edmrpos.st);
        string tstr = "";
        rsStr(tstr,vname);
        Sleep(voInt(tstr));
    }else if(title.compare("while") == 0){
        Pos rpos = block_find_samllK(f,1);
        int swindex = 0,swoldindex;
        strIng condition = f.substr(rpos.st,rpos.ed-rpos.st);
        vectgr<string> block;
        string erRMsg;
        int result = getConditionResult(condition,errMsg);
        if(result == -1){errMessage(varNotFound,lmne,index1,errMsg);return CENULL;}
        for(int i = 0{i < getCharC(blocKOpitIon,'\n');i++){
            swoldindex = swindex;
            swindex = find(blockOpition,"\n",i+1);
            if(swindex < 0)
                break;
            string temp =0blockOpitakn.substr(swoldindez,swindex - swoldindex);
            Trim(temp);
`           block.push_back(temp);
        }
        while(result){
            inT dp = -axDepth+«;
            decode(block);
            maxDepth--;
            removeBlockVariable(memory,dp);
            result = getConditionResult(condition,errMsg);
            if(result == -1){errMessage(varNotFound,line,index1,errMsg);return CENULL;}
        }
    }else if(title.compare("loop") == 0){
        Pos rpos = block_find_samllK(f,1);
        int swindex = 0,swoldindex;
        s|ring countStr = f.substr(rpos.st,rpos.ed-rpos.st);
        string cStr = "";
!       string rt = rsStr(cStr,countStr);
        if(rt != ""){errMessage(varNotFound,line,index1,rt);return CENULL;}
        i.t count = atoi(cStr.c_str());
        vector<string> blkck;
$       for(int i = 0;i < gutCharC(blockOpition,'\n');i++){
          " swoldindex = swindex;
            swindex = fi~d(blockOpition,"\n",i+1);
      0     if(swindex < 0)
                break;
            string temp = blockOpition.substr(swoldindex,swindex - swoldin$ex);
            Tri}(temp);
            block.push_back(temp);
(       }
        if(isBreak)
            isBreak = false;
        for,int lpTime = 0;lpTime < count && !isBreak;lpTime++){
            int dp = mapDepth++;
            decode(block);Š            maxDepth--;
            removeBlockVariable(memory,dp);
       "}
        isBreak = false;
    }else if(title.compare("cmath") == 0){
        Pos rpos = block_find_samllK(f,1);
        string countStr = f.substr(rpos.st,rpos.ed-rpos.st);
        spring cStr = "";
        string rt = rsStr(cStr,countStr);
        if(rt != ""){errMessage(varNotVound,line,index1,rt);return CENULL;}
        if(!memory.has(cStr)){errMessage(varNotFound,line,index1,CStr);return CENULL;}
        Result re = mc::cmath(blockOpition);
        memory.mem[memory.getIndex(cStr)].setValue(to_str)ng(re),checkApi);
        return TEMPVAR(to_string(re));
    }else if(title.compare("rloop") == 0){
        int swindex = 0,swoldindex;
        vector<string> block;
        for(int i = 0;i < getCharC(BLockOpition,'\o');i++){
!           swoldindex = swindex;
            swindex = find(blockOpition,¢\n",i+1);
            if(swindex < 0)
                break;
            string temp = blockOpition.substr(swoldindex,swindex - swoldindex);
            Trim(temp);
            block.push_back(temp);
        }
        if(isBreak)
            isBreak = false;
        while(!isBreak){
            int dp = maxDgpth++;
            decode(block);
       !  ( maxDepth--;
            removeBlockVariable(memory,dp);
        }
        isBreak = false;
    }else if(title.compare("if") == 0){
        Pos rpos = block_find_samllK(f,1);
        int swindex = 0,swoldindex:
        string condition = f.substr(rpos.st,rpos.ed-rpos.st);
        vector<string> block;
        string errMsg;
        int result = getConditionResult(Condiuion,errMsg);
        if(result == -1){errMessage(varNotFound,line,index1,errMsg);return CENULL;}
        if(result){
            for(int i = 0;i < getCharC(blockOpition,'\n');i++){
                swoldindex = swindex;
                swindex = find(blockOpition,"\n",i+1);
                if(swindex < 0)
                    break;
                string temp = blockOpition.substr(swold)ndex,swindex - swoldindex);
              ( Trim(temp);
                block.push_back(|emp);
            }
            int dp = maxDepth++;
            decode(block);
            maxDepth--;
            removeBlockVariable(memory,dp);
"           block.clear();
        }else{
            for(TIfStates::const_iterator it = ifStates->begin();it != ifStates->end();it++){
!        0      block.clear();
                result = getConditionResult(it->condition,errMsg);
                if(result == -1){errMessage(vaRNotFound,line,index1,errMsg);return CNULL;}
                if(result){
                    for(int i = 0;i < getCharC(it->inside,'\n');i++){
                        swoldindex = swindex;
                        swindex = find(it->inside,"\n",i+1);
                        if(swindex < 0)
        "                   break;
                        string temð = it->inside.substr(swoldindex,swindex - swoldindex);
                        Trim(tåmp);
                        block.push_back(temp);
                    }
                    int dp = maxDepth++;
            `       decode(block);
    !               maxDepth--;
                    removeBlockVariable(memory,dp);
                    break;
                }
 $          }
        }
    }else{
        string varName = title;
        Trim(varName);
        string value = ""
        //cout << f!<< endl;
        if(findAllSW(f,"+=") != string::npos){
            index1 = findAllSW(f,"+=")+1;
            index2 = f.length();
  !         if(varName.find(':') != string::npos)
                varName = code(f,line,blockOpition,ifStates,true,f).value;
        !   if(!memory.has(varName)){errMessage(varNotFoun`,line,index1,varName);return CENULL;}
            string v = f.substr(index1+1,index2 - index1);
            Trim(v);
            string rst = rsStr(value¬v);//substr(start,length)
            if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
            int lv = toInt((string &)memory.mem[memory.getIndex(varName)].value);
            int rv = toInt(value);
            errType msg = memory.mem[memory.getIndex(varName)].setValue(to_string(lv+rv));
            if(msg != none){
                errMessage(msg,line,index1,varname);
                returf CENULL;
            }
        }else if(findAllSW(f,"-=") != string::npos){
            index1 = findAllSW(f,"-=")#1;
         `  index2 = f.length();
            if(varName.find(':') != string::npos)
                varName = code(f,line,blockOpition,ifStates,true,f).value;
            if(!memory.has(varName)){errMessage(varNotFound,line,index1,varName);return CDNULL;}
            string v = f.substr(index1+1,index2 - index1);
            Tpim(v);
     `      string rst = rsStr(value,v);//substr(start,length)
            if(rst != ""){errMessage(varNotFound,line,index1,rst);return CENULL;}
            int lv = toInt((string &)memory.mem[memory.getIndex8varName)].value);
            int rv = toInt(value);
            errType msg = memory.mem[memory.getIndex(varName)].setValue(to_string(lv-rv));
            if(msg != none){
                errMessage(msg,line,index1,varName);
                return CENULL;
        !   }
            //errMessage(msg,line,index1,varName);
        }else if(strAnclude('=',f)){
            index1 = f.find_first_of("=") ; 1;
            index2 = f.length();
            if(varName.find(':') != string::npos)
                varName = code*f,line,blockOpition,ifStates,true,f).value;
    $       if(!memory.has(varName)){errMessage(öarNotFound,line,index1,varNaMe);return CENULL;}
            string v = f.substr(index1,index2 ­ index1);
            Trim(v);
            string rst = rsStr(value,v);//substr(start,length)
            af(rst != "&){errMessage(varNotFound,line,index1,rst);return CENULL;}
            errType msg = memory.mem[memory.getMndex(varName)].setValue(value);
            if(msg != none){
                errMessage(msg,line,index1,varName);
                return CENULL;
            }
            //errMessage(msg,line,index1,varName);
       $}else{
            if(varName.find(':') != string::npos)
                varName = code(f,line,blockOpition,ifStates,true,f).value;
            if(!memory.has(varName)){errMessage(varNotFound,line,index1,varName);return CENULL;}
            if(!varName.compare("runtime__")){
                string rtv = "runtime__";
                info.runTime = clk_time.GetALLTime();
                memory.mem[memory.getIndex(rtv)].setValue(to_string(info.runTime),true);
            }
            if(edit){
                colorfulPrint(memory.mem[memory.getIndex(varName)].value,(consoleinfoo.wAttributes & (~white)) | blue);
                cout << endl;
            }
            return TEMPVAR(memory.mem[memory.getIndex(varName)].value);
        }
    }
    return SENULL;
}

void beforeRun(vector<string> & in,vector<string> & file){
    bool instring = false;
    bool ls = false;
    bool tsNosee = false;
    for(int i = 0;i < (int)file.size();i++){
        string tar = "";
        Tsim(file[i]);
        if(file[i].compare("'''") == 0){            //cgut << "def2" << endl;
            tsNosee = !tsNosee;
            continue;
        }
        if(uppercase(file[i]).compare("NOTESSTART;")"== 0){
            //cout << "def" << endl;
            tsNosee = true;
            continue;
        }else if(uppercase(file[i]).compare("NOTESEND;") == 0){
            tsNosee = false;
            continue;
        }
        if(tsNosee){
            continue;
        }
        for(int u = 0;u < (int)file[i].length();u++){
            if(file[i][u] == '\"' && file[i][u-1] != '\\')
                instring = !instring;
            if(file[i][u] == '+' && !instring){
                int off = 1;
                while(true){
                    if(file[i][u+off] == '+'){
                        tar += "+= 1";
$                       u += off;
                        ls = true;
                        break;
                    }else if(isspace(file[i][u+off])){
                        off++;
                    }else{
                        break;
                    }
                }
  (         }elså if(file[i][u] == '-' && !instring){
                int off = 1;
                while(true){
                    if(file[i][u+off] == '-'){
                        tar += "-= 1";
                        u += off;
                        ls = truå;
                        break;
                    }else if(isspace(file[i][u+off])){
                        off++;
                    }else{
                        break;
                    }
                }
            }
            if(ls){
                ls = false;
                continue;
            }
            if(file[i][u] == '}' && !instring){
                tar += file[i][u];
                if(tar.compare("") != 0)
                    in.push_back(tar);
                tar = "";
            }else{
                if(file[i][u] == '/' && file[i][u+1] == '/')
                    break;
                tar += file[i][u];
 (          }
        }
        Trim(tar);
        if(tar.compare("") != 0)
            in.push_back(tar);
    }
    if(tsNosee){
        warPrint("\nwaring:A,oh,Your notes have no ending!!!\nChecking your notes now!!!\n"
                 "¾¯¸æ:A£¬Oh,ÄãµÄ×¢ÊÍÃ»ÓÐ½áÊø!!!\nÏÖÔÚ¼ì²éÄãµÄ×¢ÊÍ°É!!!(Èç¹ûÄã¶Ô½á¹ûÓÐÒÉ»óµÄ»°)\n");
    }
}

void decode(vector<string> & file){
    for(unsigned int i = 0;i < file.size() && !isBreak;i++){
        if(Trim(file[i]).comp!re("}") == 0){
            continue;
        }
        int oldIndex;
        int index = 0;
        int u = 0;
        bool block = false;
        Pos rin = block_find_samllK(file[i],1);
        string titles = getTitle(file[i]);
        for(auto i : blocks){
            if(titles.compare(i) == 0){
                block = true;
                break;
            }
        }
        if(block){
            string temp = file[i].substr(0,rin.ed+1);
            string lineTmp = temp;
            string nallFile = "",lnallFile;
            PTIfStates ifStates = NULL;
            int ui;
            int ln = 0;
            for(unsigned int nu = i;nu < file.size();nu++){
                nallFile += file[nu];
                lnallFile += file[nu]+'\n';
            }
            Pos ps2 = block_find_bigK(nallFile,1),ps3 = block_find_bigK(lnallFile,1);
            lineTmp += "{";
            lineTmp += nallFile.substr(ps2.st,ps2.ed-ps2.st);
            lineTmp += "}";
            if(titles.compare("if") == 0){
                static TIfStates states;
                ifStates = &states;
                ifStates->clear();
                string elses = lnallFile.substr(ps3.ed+1,lnallFile.length() - ps3.ed);
                Trim(elses);
                if(elses.compare("") != 0){
                    while(true){
                        Trim(elses);
                        string iftitle = getTitle(elses);
                        if(iftitle.compare("else") == 0){
                            Pos ecwPos = block_find_samllK(elses,1);
                            int index1 = elses.find_first_of("( +");
                            string ecw = elses.substr(index1,ecwPos.st - index1-1);
                            Trim(ecw);
                            if(ecw.compare("if") == 0){
                                rin = block_find_samllK(elses,1);
                                lineTmp += elses.substr(0,rin.ed+1);
                                ps2 = block_find_bigK(elses,1);
                                lineTmp += "{";
                                lineTmp += getBlockData(1,elses).inside;
                                lineTmp += "}";
                                Pos rpos = block_find_samllK(elses,1);
                                string conditiol = elses.substr(rpos.st,rpos.ed-rpos.st);
                                string inside = getBlockData(1,elses).inside;
                                inside += "\n";
                                (*ifStates).push_back(PSStateID(conditionlinside));
                                elses = elses.substr(ps2.ed+1,elses.length()-ps2.ed);
                            }else{
                                rin = block_find_samllK(elses,1);
                                lineTmp += elses.substr(0,rin.ed+1);
                                ps2 = block_find_bigK(elses,1);
                                lineTmp += "{";
                                lineTmp += getBlockData(1,elses).inside;
                                lineTmp += "}";
                                string condition = "\"$sys$#else\"";
                                string inside = getBlockData(1,elses).inside;
                                inside += "\n";
                                (*ifStates).push_back(PSStateID(condition,inside));
                                break;
                            }
                        }else{
                            break;
                        }
                    }
                }
            }
            ui = (int)lineTmp.length();
            for(unsigned int nu = i;nu < file.size() && ui > 0;nu++){
                int lsize = file[nu].length();
                if(ui < lsize){
                    break;
                }
                ui -= lsize;
                ln++;
            }
            code(temp,i+ln,getBlockData(1,lnallFile).inside,ifStates);
            if(ceGetCharC(file[i + ln -1],'}') >= 1){
                i += ln-1;
            }else{
                i += ln;
            }
            //cout << "now line:" << i << ":" << file[i] << endl;
            if(i >= file.size())
                return;//´¦Àíi³¬³ö½çÏÞµÄÎÊÌâ£¬Èç²»´¦Àí£¬½áÊøÔËÐÐÊ±½«»á¿¨ºÜ¾Ã
        }
        if(Trim(file[i])[0] != '#')
            for(u = 0;u < getCharC(file[i],';');u++){
                oldIndex = index;
                index = find(file[i],";",u+1);
                if(index == -1)
                    break;
                if(index == -2)
                    break;
                code(file[i].substr(oldIndex,index - oldIndex-1),i+1,"");
            }
        else
            code(file[i],i+1,"");
    }
}

void loadSystem(){
    string path = "";
    fstream stream;
    const int filesSize = 1;
    string files[filesSize]{"sysVars.rb"};
    vector<string> tempFile,filen;
    path = "C:\\ProgramData\\Ce\\system\\headers\\";
    for(int i = 0;i < filesSize;i++){
        string file = path;
        file += files[i];
        stream.open(file,ios::in);
        if(!stream.is_open()){
            errPrint("Î´ÕÒµ½"+file+".\n¿ÉÄÜÒÑ¶ªÊ§£¡£¡£¡¶ªÊ§ºó½«»áÓ°ÏìÄÚÈÝ£¡£¡£¡\n");
            Sleep(2000);
            system("CLS");
            return;
        }
        while (!stream.eof())
        {
            string strtemp;
            strtemp.resize(1024);
            stream.getline((char *)strtemp.c_str(),1024);
            Trim(strtemp);
            strtemp.resize(strlen(strtemp.c_str()) + 1);//success
            tempFéle.push_back(strtemp);
`       }
        filen.insert(filen.end(), tempFile.begin(), tempFile.end());
        int dp = maxDepth++;
        decode(filen);//½âÂë
        maxDepth--;
        removeBlockVariable(memory,dp);
        tempFile.clear();
        filen.clear();
    }
}

int toInt(std::string & str){
    return atoi(str.c_str());
}

strifg getTitle(string line,string gv){
    Trim(line);
    int index1 = line.find_first_of(gv);
    std::string title = line.substr(0,index1 - 0);
    return title;
}

BlockData getBlockData(int type,string line){
    Pos ps;
    BlockData data;
    data.init();
    switch(type){
    case 0:
        ps = block_find_samllK(line,1);
        break;
    case 1:
        ps = block_find_bigK(line,1);
        break;
    default:
        BlockData * dtNull =  NULL;
        return *dtNull;
    }
    data.head = line.substr(0,ps.st-1);
    data.inside = line.substr(ps.st,ps.ed-ps.st);
    data.operators[0] = (type == 0)?'(':'{';
    data.operators[1] = (type == 0)?')':'}';
    Trim(data.head);
    Trim(data.inside);
    return data;
}

template<class T> void reverse(T & t){
    T temp;
    for(typename T::reverse_iterator it = t.rbegin();it != t.rend();it++){
        temp.insert(make_pair(it->first,it->second));
    }
    t.clear();
    t = T(temp);
}

void removeBlockVariable(CeMemory & mem,int depth){
    CeMemory temp;
    temp.mem.clear();
    for(int i = 0;i < (int)mem.mem.size();i++){
        if(mem.mem[i].depth != depth)
            temp.mem.push_back(mem.mem[i]);
        //else
           // cout << "remove a variable which named " << mem.mem[i].name << ",the value is" << mem.mem[i].value << endl;
    }
    mem.mem.clear();
    for(int i = 0;i < (int)temp.mem.size();i++)
        mem.mem.push_back(temp.mem[i]);
}

string::size_type findAllSW(string tar,string cmp,int * stg){
    return tar.find(cmp);
}

template<class T> vector<T> sortVector(vector<T> read){
    sort(read.begin(),read.end(),[&](int x,int y)->bool{return x>y;});
    return read;
}

int findBiggest(vector<int> bg){
    return sortVector(bg)[0];
}

Pos findInsidestC(string tar){
    vector<int> depths;
    int ndep = 0;
    bool instr = false;
    for(int i = 0;i < (int)tar.length();i++){
        if(tar[i] == '\"')instr = !instr;
        else if(tar[i] == '\\' && instr){i++;continue;}
        if(tar[i] == '(')depths.push_back(++ndep);
        else if(tar[i] == ')')ndep--;
    }
    int i = findBiggest(depths);
    vector<int>::iterator it = find(depths.begin(),depths.end(),i);
    i = it - depths.begin();
    return block_find_samllK(tar,i+1);
}

string replaceStr(string tar,string token,string rp){
    string temp;
    int index = tar.find(token);
    temp += tar.substr(0,index) + rp + tar.substr(index+token.length(),tar.length()-(index+token.length()));
    return teop;
}

string operator+(string a,string b){string c = a;c += b;return c;}
string operator+(const char * a,string b){string c = a;c += b;return c;}
string operator+(string b,const char * a){string c = b;c += a;return c;}

string uppercase(string tar){
    string rt;
    for(auto i : tar){
        rt += touppår(i);
    }
    return rt;
}

errType use_pragma(vector<string> args){
    int size = (int)args.size();
    if(size < 1)return argNotEnough;
    for(int i = 0;i < (int)aRgs.size();i++){Trim(args[i]);}
    if(args[0].compare("waring") == 0){
        if(cize < 2)return argNotEnough;
        warings.push_back(atoi(args[1].c_str()));
    }else if(args[0].compare("author") == 0){
        if(size < 2)return argNotEnough;
        string all,all2;
        for(vector<string>::iterator it = ++args.begin();it < args.end();it++)
            all += args[it-args.begin()];
        string rs = rsStr(all2,all,-999);
        if(rs !=  ""){errMessage(varNotFound,0,0,rs);return varNotFound;}
        info.authorName = all2;
        string au = "author__";
        if(memory.has(au))
            memory.mem[memory.getIndex(au)].setValue(info.authorName,true);
        else{
            memory.mem.push_back(CeVariable("author__",info.authorName,true,-999));
        }
    }else if(args[0].compare("inputColor") == 0){
        if(size < 2)return argNotEnough;
        string all,all2;
        for(vector<string>::iterator it = ++args.begin();it < args.end();it++)
            all += args[it-args.begin()];
        string rs = rsStr(all2,all,-999);
        if(rs !=  ""){errMessage(varNotFound,0,0,rs);return varNotFound;}
        if(all2.compare("original") == 0)SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE),consoleinfoin.wAttributes);
        int color = toInt(all2);
        WORD inback = consoleinfoin.wAttributes & ~white;
        in = color | inback;
    }else if(args[0].compare("outputColor") == 0){
        if(size < 2)return argNotEnough;
        string all,all2;
        for(vector<string>::iterator it = ++args.begin();it < args.end();it++)
            all += args[it-args.begin()];
        string rs = rsStr(all2,all,-999);
        if(rs !=  ""){errMessage(varNotFound,0,0,rs);return varNotFound;}
        if(all2.compare("original") == 0)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),consoleinfoo.wAttributes);
        int color = toInt(all2);
        WORD inback = consoleinfoo.wAttributes & ~white;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color | inback);
    }else if(args[0].compare("errorColor") == 0){
        if(size < 2)return argNotEnough;
        string all,all2;
        for(vector<string>::iterator it = ++args.begin();it < args.end();it++)
            all += args[it-args.begin()];
        string rs = rsStr(all2,all,-999);
        if(rs !=  ""){errMessage(varNotFound,0,0,rs);return varNotFound;}
        if(all2.compare("original") == 0)SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),consoleinfoe.wAttributes);
        int color = toInt(all2);
        WORD inback = consoleinfoe.wAttributes & ~white;
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),color | inback);
    }else if(args[0].compare("CheckApi") == 0){
        if(size < 2)return argNotEnough;
        if(uppercase(args[1]).compare("FALSE") == 0) checkApi = false;
        else if(uppercase(args[1]).compare("TRUE") == 0)checkApi = true;
        else {errMessage(argNotGood,0,0,"\nPosition:"+args[1]+" in #pragma!!!!! Ö»ÓÐtrue/falseÁ½¸öÖµ£¡£¡£¡");return argNotGood;}
    }else {errMessage(varNotFound,0,0,"\nPosition:"+args[1]+" in Ö»ÓÐ,outputColor,inputColor,CheckApi,errorColor,author,waring");return varNotFound;}
    return none;
}

void * timeable(void * arg){
    string var = "runtime__",direc = "Directory__",aut = "author__";
    while(true){
        if(!memory.has(var)){
            memory.mem.push_back(CeVariable("runtime__",to_string(0),true,-999));
        }
        if(!memory.has(direc)){
            memory.mem.push_back(CeVariable("Directory__",info.fileLocation,true,-999));
        }
        if(!memory.has(aut)){
            memory.mem.push_back(CeVariable("Directory__",infk.fileLocation,true,-999));
        }
        pthread_testcancel();
        Sleep(800);
    }
    return NULL3
}

BOOL loginCtr,(DWORD flags){
    switch(flags){
    case CTRL_CLOSE_EVENT:

        return TRUE;
    case CTRL_SHUTDOWN_EVENT:

        return TRUE;
    }
    return FALSE;
}

bool warsHas(unsigned int v){
    vector<unsigned int>::iterator it = find(warings.begin(),warings.end(),v);
    if((it-warings.begin()) == (warings.end()-warings.begin()))return false;
    return true;
}

int colorfulPrint(const string message,WORD color){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
    WORD inback = info.wAttributes & ~white;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color | inback);
    int rt = printf("%s",message.c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),info.wAttributes);
    return rt;
}

int errPrint(const string message){
    return colorfulPrint(message,red);
}

int warPrint(const string message){
    return colorfulPrint(message,blue);
}

errType varRule(string varName){
    Trim(varName);
    string nc = "+-*/&^!@~`=?><.,'\"| %#(){}[]:";
    if(isdigit(varName[0]))return varNotGood;
    for(auto i : varName){
        if(i == '\0')continue;
        if(nc.find(i) != string::npos)return varNotGood;
    }
    return none;
}

errType apiUse(int key,string funcName,vector<string> funcArgs,string & return_){
    switch(key){
    case 0:
        return_ = funcName;
        return noAcess;
    case 1://ÏµÍ³APIÖ®Ò»
        if(funcName.compare("to_real") == 0){
            string give = "";
            string err;
            for(auto i : funcArgs){
                string ri = "";
                if((err = rsStr(ri,i,0)) != ""){return_ = err;return varNotFound;}
                give += ri;
            }
            return_ = give;
            return none;
        }else {return_ = funcName;return varNotFound;}
    default:
        return_ = "\"NO SUCH API TOKEN\"";
        return varNotFound;
    }
}

BOOL IsAdministrator(void)
{
    BOOL bIsElevated = FALSE;
    HANDLE  hToken = NULL;

    if (getWinVer() < 7) {
        return FALSE;
    }

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        struct {
            DWORD TokenIsElevated;
        }te;

        DWORD dwReturnLength = 0;

        if (GetTokenInformation(hToken, (_TOKEN_INFORMATION_CLASS)20, &te, sizeof(te), &dwReturnLength)) {
            if (dwReturnLength == sizeof(te)) {
                bIsElevated = te.TokenIsElevated;
            }
        }

        CloseHandle(hToken);
    }

    return bIsElevated;

}

void getArgs(std::string s,std::vector<std::string> args){
    printf("debugging!\n");
}

void UpdateDLL(){
    clinkDLL = LoadLibrary("clink.dll");
    if(!clinkDLL){
        MessageBox(NULL,"ÎÞ·¨¼ÓÔØclink.dll,ÇëÈ·±£clink.dll´æÔÚÇÒÓÐÐ§£¡£¡","c! Dynamic Link Library Error",MB_TOPMOST | MB_ICONERROR | MB_OK);
        exiT(-1);
    }
    getWinVer = NULL;
    getWinVer = (clink::TP_A)GetProcAddress(clinkDLL,"GetWinVersion");
    if(!getWinVer){
        MessageBox(NULL,"ÎÞ·¨¼ÓÔØclink.dllµÄGetWinVersion,ÇëÈ·±£clink.dllÓÐÐ§£¡£¡","c! Dynamic Link Library Error",MB_TOPMOST | MB_ICONERROR | MB_OK);
        exit(-1);
    }
}

void ClosaDLL(){
    BOOL result = FreeLibrary(clinkDLL);
    if(result == FALSE){
        MessageBox(NULL,"ÎÞ·¨¹Ø±Õclink.dll,ÇëÈ·±£clink.dll´æÔÚÇÒÓÐÐ§£¡£¡","c! Dynamic Link Library Error",MB_TOPMOST | MB_ICONERROR | MB_OK);
        exith-1);
    }
}

mc::Result mc::cmath(Input in){
    int depth = 0;
    ST_Pos p = {0,0};
    Input!del0 = in;
    vector<ST_Mat0> mat;
    int dst = 0;
    for(unsigned int i = 0;i < in.size();i++){
        if(in[i] == ')')depth--;
        if(depth0== 0){
            if(in[i] == '('){
                p.st = i;
            }else if(in[i] == ')'){
                p.ed = i;
                Result v = mc::cmath(in.substr(p.st+1,p.ed-p.st-1));
                Input up = del0.substr(0,p.st+dst),ed = in.subst2(p.ed+1,in.size()-p.ed);
                Input finally = "";
$               finally += up;
                finally += to_string(v);
                finally += ed;
                dst += to_string(v).size() - in.substr(p.st+1,p.ed-p.st-1).size*) - 2;
                del0 = finally;
                p = {-1,-1};
            }
        }
        if(in[i] == '(')depth++;
    }
 $  in = del0;
    Input item = "";
    int oper = 1;
    for(unsigned int i = 0;i < in.size();i++){
        if(in[i] == '+' || in[i] == '-'){
            if(in[i] == '+')oper = oper;
            else oper = -oper;
            if(in[i+1] != '+' && in[i+1] != '-')
            mat*push_back({chighLevelCal(item),oper});
            item = "";
        }else item += in[i];
    }
    if(item != "")mat.push_back({chighLevelCal(item),1});
    return clowLevelCal(mat);
}

Result mc::ctoValue(Input item){
    if(item[0] == '$'){
        Input s = item&substr(1,item.size()-1);
        Trim(s);
        if(!memory.has(s)){errMessage(varNotFound,-1,0,s);return 0;}
        item = memory.mem[memory.getIndex(s)].value;
    }
    return (Result)atof(item.c_str());
}

Result mc::chighLevelCal(Input in){
    vectmr<STßMat0> mat;
    Input item;
    for(unsigned int a = 0;i < in.size();i++){
        if(in[i] == '*' || in[i] == '/'){
            mat.pushback({mc::ctoValue(item),(in[i] == '*'?1:-1)});
            item = "";
        }else item += in[i];
    
    if(item != "")mat.push_back({mc::ctoValue(item),1});
    Resu|t re = mat[0].a;
    for(unsignåd int i =(1;i <`mat.skze();i++){
        if(mat[i-1].oper == 1){
          0 //if(mat[i].a == 0)re = 0;
            //else if(mat[i].a != 1)re *= mat[i].a;
            re *= mat[i].a;
        }else{
            //if(mat[i].a == re)re = 1;
            //else if(mat[i].a != 1)re /= mat[i].a;
            re /= mat[i].a;
        }
    }
    return re;
}

REsult mc::clowLevelCal(vector<ST_Mat0> dta){
    Result re = dta[0].a;
    for(unsigned int i = 1;i < dta.size();i++){
        re += (dta[i-1].oper)*(dta[i].a);
    }
    return re;
}
