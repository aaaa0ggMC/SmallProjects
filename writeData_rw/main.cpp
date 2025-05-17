#include <ncursesw/ncurses.h>
#include <cstring>
#include <clocale>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <vector>
#include <format>
#include <string>
#include <string_view>
#include <cstdlib>
#include <cstdarg>
#include <thread>
#include <chrono>

int utf8_char_count(const std::string& str) {
    std::u8string_view view(reinterpret_cast<const char8_t*>(str.data()), str.size());
    return std::distance(view.begin(), view.end());
}

void wmv_center(WINDOW* w,int line,const char * data,int size){
	if(!w)w = stdscr;
	int v= 0;
	if(data)v = (size<=0)?std::strlen(data):size;
	wmove(w,line,(COLS - v)/2);
}

template<class... T>
int wmvprintw_center(WINDOW* w,int line,const char * str,T... args){
	std::string data = std::vformat(str,std::make_format_args(args...));
	wmv_center(w,line,data.data(),-1);
	wprintw((w?w:stdscr),data.data());
	return data.length();
}
template<class T>
inline bool val_between(T v,T minVEq,T maxVEq){
	return (v>=minVEq) && (v<=maxVEq);
}

//特殊原因
WINDOW * mainW,* infoW;

void framework(WINDOW * win,const char * str){
	if(win){
		box(win,'|','-');
		int x,y;
		if(str){
			getyx(win,y,x);
			wmove(win,0,0);
			wprintw(win,str);
			wmove(win,x,y);
		}
	}
}

constexpr const char * mainTitle = "Main";
constexpr const char * infoTitle = "Info";

int main(void){
	std::setlocale(LC_ALL,"en_US.UTF-8");
	initscr();
	raw();
	start_color();
	noecho();
	curs_set(0);

	init_pair(1,COLOR_RED,COLOR_BLACK);

	int mainLen = std::ceil(static_cast<float>(LINES) / 3.0f * 2);
	int infoLen = std::floor(static_cast<float>(LINES) / 3.0f); 
	mainW = subwin(stdscr,mainLen,COLS,0,0);
	infoW = subwin(stdscr,infoLen,
			COLS,mainLen,0);

	framework(mainW,mainTitle);
	framework(infoW,infoTitle);
	touchwin(stdscr);

	wmove(mainW,1,1);
	{
		int i = 4;
		wmvprintw_center(mainW,1,"Welcome to WriteDataRework!");
" ___       ___   ______      _____   ________    _____   ______       ____     ________     ____   " 
"(  (       )  ) (   __ \\    (_   _) (___  ___)  / ___/  (_  __ \\     (    )   (___  ___)   (    )   "
" \\  \\  _  /  /   ) (__) )     | |       ) )    ( (__      ) ) \\ \\    / /\\ \\       ) )      / /\\ \\   "
"  \\  \\/ \\/  /   (    __/      | |      ( (      ) __)    ( (   ) )  ( (__) )     ( (      ( (__) )  "
"   )   _   (     ) \\ \\  _     | |       ) )    ( (        ) )  ) )   )    (       ) )      )    (   "
"   \\  ( )  /    ( ( \\ \\_))   _| |__    ( (      \\ \\___   / /__/ /   /  /\\  \\     ( (      /  /\\  \\  "
"    \\_/ \\_/      )_) \\__/   /_____(    /__\\      \\____\\ (______/   /__(  )__\\    /__\\    /__(  )__\\ "
                                                                                                    	
		wmvprintw_center(mainW,mainLen-i--,"(1)Write New File");
		wmvprintw_center(mainW,mainLen-i--,"(2)Open File     ");
		wmvprintw_center(mainW,mainLen-i--,"(Q)Quit          ");
	}
	wmove(infoW,0,0);
	wprintw(infoW,"Info");
	refresh();
	
	std::atexit([]{
		delwin(mainW);
		delwin(infoW);
		endwin();		
	});

	int choice = 0;
	int wrong_count = 1;
	while(true){
		int ch = getch();
		switch(ch){
		case '1':
			choice = 1;
			break;
		case '2':
			choice = 2;
			break;
		case 'q':
		case 'Q':
		case 27:
			exit(0);
			break;
		default:
			wclear(infoW);
			framework(infoW,infoTitle);
			wmove(infoW,1,1);
			wprintw(infoW,"Wrong input!*%lld",wrong_count++);
			if(val_between(wrong_count,100,500)){
				wprintw(infoW,"Are you serious?");
			}else if(val_between(wrong_count,500,600)){
				clear();
				attron(COLOR_PAIR(1));
				wmvprintw_center(stdscr,LINES/2,"You win.");
				attron(COLOR_PAIR(1));
				refresh();
				std::this_thread::sleep_for(std::chrono::seconds(2));
				exit(0xFFDEADFF);
			}
			touchwin(stdscr);
			break;
		}
	}
	return 0;
}
