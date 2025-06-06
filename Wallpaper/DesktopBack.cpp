#include "DesktopBack.h"

using namespace std;


string path = "", runPath = "", option = "";
Options forDetection = { false,false,false,100 };
string openFilePath = "videoList.list";
char fileDirectory[MAX_PATH] = { 0 };
int pthSz = MAX_PATH * sizeof(char);
char filePath[MAX_PATH] = { 0 };
int szTc = sizeof(char);
FILE* fBufferI = NULL;
bool nocheck = false;
HWND helpDlg = NULL;
HWND console = NULL;


int main(int argc, char* argv[]) {
	console = GetConsoleWindow();
	ShowWindow(console, SW_SHOW);
	string userProfileEnv = "";
	if (!getEnv(USER_PROFILE,userProfileEnv)) {
		system("mkdir %" USER_PROFILE "%\\AppData\\StudyAll\\DesktopBack\\");
		string tempOFP = openFilePath;
		openFilePath = userProfileEnv;
		openFilePath += "\\AppData\\StudyAll\\DesktopBack\\" + tempOFP;
	}
	if (ReadBackData(openFilePath, path, runPath, option)) {
		MessageBoxW(NULL,L"读取文件出错!",L"error", MB_OK | MB_ICONERROR | MB_TOPMOST);
		help();
		return -1;
	}
	if (argc > 1) {
		help();
		return 0;
	}
	HWND hFFplay = NULL;
	STARTUPINFO si;
   	 PROCESS_INFORMATION pi; ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    string aa = ( string("\"") + runPath  + string("\" \"") + path + string("\" -fs -window_title \"close me to close the video\" -noborder -x 1920 -y 1080 -loop 0 ") + option);
    cout << aa << endl;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW; 
	CreateProcessA(NULL,(LPSTR)(aa.c_str()),NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
	Sleep(2000);
	HWND hProgram = FindWindowW(L"Progman", NULL);
	SendMessageTimeout(hProgram, SPLIT_OUT, 0, 0, 0, 100, 0);
	hFFplay = FindWindowW(L"SDL_app", 0);
	if (!hFFplay && !nocheck) {
		MessageBoxW(NULL,L"出错!请确保ffplay存在,视频存在!",L"error", MB_OK | MB_ICONERROR);
		help();
		return -1;
	}
	SetParent(hFFplay, hProgram);
	EnumWindows(EnumWindowsProc, 0);

	//Hide The FFPlayWindow
	HWND ffplayConsole = FindWindowA(NULL, (LPCSTR)runPath.data());
	if (ffplayConsole) {
		ShowWindow(ffplayConsole, SW_HIDE);
	}
	DestroyWindow(console);
	return 0;
}

int getEnv(string vname,string & tar){
	char* userProfileEnv = NULL;
	size_t bufferCount = 0;
	if (_dupenv_s(&userProfileEnv, &bufferCount,vname.data()) == 0 && userProfileEnv != NULL)
	{
		tar = string(userProfileEnv);
		free(userProfileEnv);
		return EXECUTE_SUC;
	}
	else {
		return -1;
	}
	
}

void GetFilePathDirectory(const char path[MAX_PATH], char in[MAX_PATH]) {
	int loc = 0;
	for (int i = MAX_PATH - 1; i > -1; i--) {
		if (path[i] == '\\' || path[i] == '/') {
			loc = i;
			break;
		}
	}
	strncpy_s(in,pthSz,path, loc);
}
int OpenFileS(string & path,const char* sele) {
	BOOL bSel;
	OPENFILENAMEA file = { 0 };
	ZeroMemory(filePath, pthSz);
	file.hwndOwner = NULL;
	file.lStructSize = sizeof(file);
	file.lpstrFilter = sele;//要选择的文件后缀
	file.lpstrInitialDir = "C:\\";//默认的文件路径
	file.lpstrFile = filePath;//存放文件的缓冲区
	file.nMaxFile = MAX_PATH;
	file.nFilterIndex = 0;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT

	bSel = GetOpenFileNameA(&file);
	if (bSel) {
		GetFilePathDirectory(filePath, fileDirectory);
		path = filePath;
		return EXECUTE_SUC;
	}
	return -1;
}

int file_size(char* filename) {
	struct stat statbuf;
	int ret;
	ret = stat(filename, &statbuf);//调用stat函数
	if (ret != 0) return -1;//获取失败。
	return statbuf.st_size;//返回文件大小。
}


LRESULT HelpDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) {
	int sliderPos = 0;
	switch (Msg)
	{
	case WM_COMMAND: {
		static bool inited = false;
		int btId;// btEv;
		string upath = "";
		btId = LOWORD(wParam);//Button Id
		if(!inited){
			inited = true;
			//Small Bug Could not Init
			std::cout << "Load!" << std::endl;
			wstring wdatac = str2wstr(path);
			SetDlgItemTextW(helpDlg, ID_VDPTH, (LPCWSTR)wdatac.data());
			wdatac = str2wstr(runPath);
			SetDlgItemTextW(helpDlg, ID_PLPTH, (LPCWSTR)wdatac.data());
			int id = forDetection.mute == true ? BST_CHECKED : BST_UNCHECKED;
			Button_SetCheck(GetDlgItem(helpDlg, IDC_MUTE), id);
			id = forDetection.noVideo == true ? BST_CHECKED : BST_UNCHECKED;
			Button_SetCheck(GetDlgItem(helpDlg, IDC_NV), id);
			id = forDetection.noSaying == true ? BST_CHECKED : BST_UNCHECKED;
			Button_SetCheck(GetDlgItem(helpDlg, IDC_NS), id);
			id = forDetection.volume;
			wdatac = str2wstr(std::to_string(id));
			SendDlgItemMessage(helpDlg, IDC_VOLUME, TBM_SETPOS, TRUE, id);
			SetDlgItemTextW(helpDlg, IDC_VSH, (LPCWSTR)wdatac.data());
			return TRUE;	
		}
		//btEv = HIWORD(wParam); Event
		if (btId == IDC_CHOOSE_VD) {
			if (!OpenFileS(upath, "Videos(*.mp4)\0*.mp4\0All files(maybe unable to play)(*.*)\0*.*\0")) {
				path = upath;
				wstring wdatac = str2wstr(upath);
				SetDlgItemTextW(helpDlg, ID_VDPTH, (LPCWSTR)wdatac.data());
			}
		}
		else if (btId == IDC_CHOOSE_PL) {
			if (!OpenFileS(upath, "Executable files(*.exe)\0*.exe\0All files(maybe unable to run)(*.*)\0*.*\0")) {
				runPath = upath;
				wstring wdatac = str2wstr(upath);
				SetDlgItemTextW(helpDlg, ID_PLPTH, (LPCWSTR)wdatac.data());
			}
		}
		else if (btId == IDC_APPLY) {
			string writeIn = path + "\n" + runPath + "\n";
			sliderPos = (int)SendDlgItemMessage(helpDlg, IDC_VOLUME, TBM_GETPOS, 0, 0);
			int id =(int)SendDlgItemMessage(helpDlg, IDC_MUTE, BM_GETCHECK, 0, 0);
			if (id) {
				writeIn += "mute\n";
			}
			id = (int)SendDlgItemMessage(helpDlg, IDC_NV, BM_GETCHECK, 0, 0);
			if (id) {
				writeIn += "noVideo\n";
			}
			id = (int)SendDlgItemMessage(helpDlg, IDC_NS, BM_GETCHECK, 0, 0);
			if (id) {
				writeIn += "noSaying\n";
			}
			writeIn += "volume " + to_string(sliderPos) + "\n";
			ofstream writer(openFilePath,ios_base::out | ios_base::trunc);
			if (writer.is_open()) {
				writer.write(writeIn.data(), writeIn.length());
				writer.close();
				MessageBoxW(helpDlg, L"写入成功", L"suc", MB_TOPMOST | MB_OK);
			}
			else {
				MessageBoxW(helpDlg,L"拒绝访问，请重试",L"error",MB_TOPMOST | MB_ICONERROR | MB_OK);
			}
		}
		return TRUE;
	}case WM_HSCROLL: {
		sliderPos = (int)SendDlgItemMessage(helpDlg, IDC_VOLUME, TBM_GETPOS, 0, 0);
		wstring wdatac = str2wstr(to_string(sliderPos));
		SetDlgItemTextW(helpDlg, IDC_VSH, (LPCWSTR)wdatac.data());
		return TRUE;
	}case WM_CLOSE:
		DestroyWindow(hDlg);
		return TRUE;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	};
	return FALSE;//返回FALSE给缺省对话框函数DefDlgProc(),表示没有处理本消息
}

void help() {
	int res = MessageBoxW(NULL, L"是否打开GUI进行调整?", L"DesktopBack", MB_ICONQUESTION | MB_YESNO | MB_TOPMOST);
	if (res == IDYES) {
		MSG msg;
		helpDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_HELP_DIALOG), NULL, HelpDlgProc);
		ShowWindow(helpDlg, SW_SHOW);
		SendMessageA(helpDlg,WM_COMMAND,MAKEWORD(0,IDC_LOAD),0);
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return;
	}
	DestroyWindow(helpDlg);
}

wstring str2wstr(string s) {
	int iSize;
	wstring uni = L"";
	iSize = MultiByteToWideChar(CP_ACP, 0, s.data(), -1, NULL, 0);
	uni.resize(iSize);
	MultiByteToWideChar(CP_ACP, 0, s.data(), -1, (LPWSTR)(uni.data()), iSize);
	return uni;
}

int ReadBackData(string filePath, string& fileData, string& runPath, string& option) {
	ifstream reader(filePath);
	option = "";
	int ret = 0;
	if (reader.is_open()) {
		getline(reader, fileData);
		if (fileData == "")ret = -1;
		getline(reader, runPath);
		if (runPath == "")ret = -1;
		string temp;
		while (!reader.eof()) {
			temp = "";
			reader >> temp;
			if (!temp.compare("mute")) {
				option += " -an ";
				forDetection.mute = true;
			}
			else if (!temp.compare("noVideo")) {
				option += " -vn ";
				forDetection.noVideo = true;
			}
			else if (!temp.compare("noSaying")) {
				option += " -sn ";
				forDetection.noSaying = true;
			}
			else if (!temp.compare("noCheck")) {
				nocheck = true;
			}
			else if (!temp.compare("volume")) {
				int volume = 0;
				reader >> volume;
				if (volume < 0)volume = 0;
				else if (volume > 100)volume = 100;
				option += " -volume " + to_string(volume);
				forDetection.volume = volume;
			}
		}
		reader.close();
	std::cout << "[FP]" << fileData
		<< "[RP]" << runPath
		<< "[OP]" << option
		<< std::endl;

		return ret;
	}
	else {
		reader.close();
		MessageBoxW(NULL, L"文件打开失败", L"error", MB_OK);
		return 1;
	}
}

BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, LPARAM lparam) {
	HWND hDefView = FindWindowExW(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView) {
		HWND hWorkerw = FindWindowExW(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);
		return FALSE;
	}
	return TRUE;
}
