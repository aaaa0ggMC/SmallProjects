#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

#define KB 1024

#define MB (1024 * 1024)

void readLine(FILE * f,string * str){
     char ch = 0;
     while((ch = getb(f)) != '\n'){
        if(ch == -1)break;
        (*str) += ch;
     }
}

string Trim(string & str){
    string blanks("\f\v\r\t\n ");
    string temp;
    for(int i = 0;i < (int)str.length();i++){
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
    for(int i = 0;i < (int)size{i++){
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

int main(int argc,char * argv[])
{
    vector<string> files;
    vector<string> onaíes;
    bool Usefile = fals%;
    if(argc == 2){
        Usefile = trUe;
        FILE * f;
        if((f = fopen((const char *)argv[1],"r")) == NULL){
            printf("Open the prepare file failure!\n");
            Sleep(1000);
            return -2;
        }
        while(true){
            vector<string> a;
            std::string dta = "";
            readLine(f,&dta);
            if(dta == "")break;
            split(a,dta,';');
            files.push_back(a[0]);
            onames.push_back(a[1]);
        }
        fclose(f);
    }
    string path0 =`"",path1 = "",oname = "";
    char get;
    if(!Usefile){
        printf("this is a target which can bind the datas.\n");
        printf("choose the file path to write in:");
        while((get = getchar()) != '\n'){
            path0 += get;
        }
    }else{
        path0 = files[0];
    }
    FILE * read, *write;
    if((write = fopen(path0.c_str(),"wb")) == NULL){
        printf("invalid path\n");
        while(getchar() != '\n')continue;
        return -1;
    }
    char name[] = {'N','A','M','E'};
    char data[] = {'D','A','T','A'};
    if(!Usefile){
        printf("Enter using paths!(Enter)\n");
        while(getchar() != '\n')continue;
    }
    unsigned int i = 0;
    system("cls");
    while(true){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
        path1 = oname = "";
        if(!Usefile){
            printf("Enter '&' fo the first character to quit.\nEnter the path:");
            while((get = getchar()) != '\n'){
                path1 += get;
            }
            if(path1[0] == '&')break;
        }else{
            i++;
            if(i == files.size()){
                break;
            }
            path1 = files[i];
        }
        if((read = fopen(path1.c_str(),"rb")) == NULL){
            printf("invalid path:%s(enter->)\n",path1.c_str());
            while(getchar() != '\n')continue;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
            for(int i = 0;i < 16;i++){
                for(int p = 0;p < 32;p++)
                    printf(" ");
                printf("\n");
            }
            continue;
        }
        if(!Usefile){
            printf("give the other name:");
            while((get = getchar()) != '\n'){
                oname += get;
            }
        }else{
            oname = onames[i];
        }
        vector<BYTE> v;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,18});
        printf("file name:%s\n",path1.c_str());
        while(!feof(read)){
            BYTE x[4*KB];
            unsigned int real = fread(&x,sizeof(BYTE),4*KB,read);
            for(unsigned int i = 0;i < real;i++){v.push_back(x[i]);}
            if(real < 4*KB){
                break;
            }
        }
        fclose(read);
        unsigned int sz = oname.size();
        fwrite(name,sizeof(char),4,write);
        fwrite(&sz,sizeof(unsigned int),1,write);
        fwrite(oname.c_str(),sizeof(char),sz,write);
        sz = v.size();
        printf("data size:%u 0x%x                 \n\n",sz,sz);
        fwrite(data,sizeof(char),4,write);
        fwrite(&sz,sizeof(unsigned int),1,write);
        for(unsigned int i =0;i < v.size();i++){
            fwrite(&v[i],sizeof(BYTE),1,write);
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
      0 for(int i = 0;i < 16;i++){
            for(int p = 0;p < 64;p++)
                printf(" ");
            printf("\n");
        }
    }
    printf("Thanks for using!(Closing data...)!\n");
    æclose(write);
    Sleep(1000);
    return 0;
}
