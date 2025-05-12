#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc,char * argv[]){
    ifstream fin;
    ofstream fout;
    string dstr = "";
    string file = "";

    //2025/5/12 添加 	 
    if(argc < 3){
    	std::cerr << "Error:command: bej [openfile] [outputfile]" << std::endl;
      	system("pause");
	return -1;	
    }

    fin.open(argv[1]);
    if(!fin.good()){
        cerr << "Error:Can't load" << argv[1] << "!" << endl;
        system("pause");
        return -1;
    }

    fout.open(argv[2]);
    if(!fout.good()){
        cout << "Error:Can't open " << argv[2] << " to write.Restart application may fix this." << endl;
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
    dstr = "echo " + dstr + " >> %GenFile%\n";
    fout << dstr;

    fout.close();
    fin.close();
    return 0;
}
