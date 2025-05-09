#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    string dstr = "";
    string file = "";

    fin.open("GameGen.java");
    if(!fin.good()){
        cout << "Error:No java file (root.java) here!" << endl;
        system("pause");
        return -1;
    }

    fout.open("out.txt");
    if(!fout.good()){
        cout << "Error:Can't open out.txt to write.Restart application may fix this." << endl;
        system("pause");
        return -1;
    }


    istreambuf_iterator<char> ibegin(fin),iend;
    copy(ibegin,iend,back_inserter(file));

    //cout << file << endl;
    //system("pause");

    for(unsigned int i = 0;i < file.size();i++){
        if(file[i] != '\n'){
            if(file[i] == '\t')dstr += " ";
            else if(file[i] == '>')dstr += "^>";
            else if(file[i] == '<')dstr += "^<";
            else if(file[i] == '^')dstr += "^^";
            else dstr += file[i];
        }else if(dstr.length() >= 512){
            dstr = "echo." + dstr + " >> %GenFile%\n";
            fout << dstr;
            dstr = "";
        }
    }
    dstr = "echo." + dstr + " >> %GenFile%\n";
    fout << dstr;

    fout.close();
    fin.close();
    return 0;
}
