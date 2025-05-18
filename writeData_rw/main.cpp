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
	if(data || size>=0)v = (size<=0)?std::strlen(data):size;
	wmove(w,line,(COLS - v)/2);
}

template<class... T>
int wmvprintw_center(WINDOW* w,int line,const char * str,const T&... args){
	std::string data = std::vformat(str,std::make_format_args(args...));
	wmv_center(w,line,data.data(),-1);
	wprintw((w?w:stdscr),data.data());
	return data.length();
}
template<class T>
inline bool val_between(T v,T minVEq,T maxVEq){
	return (v>=minVEq) && (v<=maxVEq);
}

template<class... T>
void framework(WINDOW * win,const char * strv,const T&... args){
	if(win){
		box(win,'|','-');
		int x,y;
		if(strv){
			std::string str = std::vformat(strv,std::make_format_args(args...));
			wmove(win,0,0);
			wprintw(win,str.c_str());
		}
	}
}

//特殊原因
WINDOW * mainW,* infoW;
int mainLen,infoLen;
constexpr const char * mainTitle = "Main";
constexpr const char * infoTitle = "Info";
constexpr const int col_past = 3,col_now = 2,col_future = 1;

enum class Choice{
	Menu,
	Write,
	Open,
	Exit
};

void clear_win(WINDOW*win,char ch,int from_x,int from_y,int to_x,int to_y){
	if(!win)win = stdscr;
	for(int i = from_y;i <= to_y;++i){
		for(int j = from_x;i <= to_x;++i){
			wmove(win,j,i);
			waddch(win,ch);
		}
	}	
}

Choice page_open(){
	return Choice::Menu;
}

Choice page_write(){
	//Init
	wclear(mainW);
	wclear(infoW);
	framework(infoW,"{}--{}",infoTitle,"Use arrow keys <up><down> to scroll.--Press Q to return to menu");
	framework(mainW,"{}--{}",mainTitle,"Use arrow keys <left><right> to scroll procedures.");
	touchwin(stdscr);

	bool running = true;
	int progress = 0;
	std::vector<const char *> names = {
		"(SelectStorer)",
		"(SelectFiles)",
		"(Finish)"
	};

	auto show_progress = [&]{
		//Step 1: Clear the first line
		clear_win(mainW,' ',1,1,COLS-1,1);	
		int size= 0;
		for(int i = 0;auto & v : names){
			if(i){
				//makeup += "---";
				size += 3;
			}
			size += 1 + std::strlen(v);
			++i;	
		}
		wmv_center(mainW,1,NULL,size);

		for(int i = 0;auto & v : names){
			if(i){
				waddstr(mainW,"---");
			}
			if(i < progress){
				wattron(mainW,COLOR_PAIR(col_past));
				waddstr(mainW,"o");
				waddstr(mainW,v);
				wattroff(mainW,COLOR_PAIR(col_past));
			}else if(i == progress){
				wattron(mainW,COLOR_PAIR(col_now));
				waddstr(mainW,"v");
				waddstr(mainW,v);
				wattroff(mainW,COLOR_PAIR(col_now));
			}else{
				wattron(mainW,COLOR_PAIR(col_future));
				waddstr(mainW,"x");
				waddstr(mainW,v);
				wattroff(mainW,COLOR_PAIR(col_future));
			}
			++i;
		}

		touchwin(stdscr);
	};

	while(running){
		char ch;
		show_progress();
		if(progress >= names.size()){
			running = false;
			continue;
		}
		getch();
		switch(progress){
			
		}
		++progress;
	}

	return Choice::Menu;
}

Choice page_menu(){
	//Init
	wclear(mainW);
	wclear(infoW);
	framework(mainW,mainTitle);
	framework(infoW,infoTitle);
	touchwin(stdscr);

	wmove(mainW,1,1);
	{
		int i = 4;
		wmvprintw_center(mainW,1,"Welcome to WriteDataRework!");
		//LOGO
		wmvprintw_center(mainW,2," ___       ___   ______      _____   ________    _____   ______       ____     ________     ____   "); 
		wmvprintw_center(mainW,3,"(  (       )  ) (   __ \\    (_   _) (___  ___)  / ___/  (_  __ \\     (    )   (___  ___)   (    )   ");
		wmvprintw_center(mainW,4," \\  \\  _  /  /   ) (__) )     | |       ) )    ( (__      ) ) \\ \\    / /\\ \\       ) )      / /\\ \\   ");
		wmvprintw_center(mainW,5,"  \\  \\/ \\/  /   (    __/      | |      ( (      ) __)    ( (   ) )  ( (__) )     ( (      ( (__) )  ");
		wmvprintw_center(mainW,6,"   )   _   (     ) \\ \\  _     | |       ) )    ( (        ) )  ) )   )    (       ) )      )    (   ");
		wmvprintw_center(mainW,7,"   \\  ( )  /    ( ( \\ \\_))   _| |__    ( (      \\ \\___   / /__/ /   /  /\\  \\     ( (      /  /\\  \\  ");
		wmvprintw_center(mainW,8,"    \\_/ \\_/      )_) \\__/   /_____(    /__\\      \\____\\ (______/   /__(  )__\\    /__\\    /__(  )__\\ ");
                                                                                                    	
		wmvprintw_center(mainW,mainLen-i--,"(1)Write New File");
		wmvprintw_center(mainW,mainLen-i--,"(2)Open File     ");
		wmvprintw_center(mainW,mainLen-i--,"(Q)Quit          ");
	}
	wmove(infoW,0,0);
	wprintw(infoW,"Info");
	refresh();
	
	Choice choice = Choice::Menu;
	int wrong_count = 1;
	while(choice == Choice::Menu){
		int ch = getch();
		switch(ch){
		case '1':
			choice = Choice::Write;
			break;
		case '2':
			choice = Choice::Open;
			break;
		case 'q':
		case 'Q':
		case 27:
			choice = Choice::Exit;
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
				attroff(COLOR_PAIR(1));
				refresh();
				std::this_thread::sleep_for(std::chrono::seconds(2));
				exit(0xFFDEADFF);
			}
			touchwin(stdscr);
			break;
		}
	}
	return choice;
}

int main(void){
	std::setlocale(LC_ALL,"en_US.UTF-8");
	initscr();
	raw();
	start_color();
	noecho();
	curs_set(0);

	init_pair(col_future,COLOR_RED,COLOR_BLACK);
	init_pair(col_now,COLOR_YELLOW,COLOR_BLACK);
	init_pair(col_past,COLOR_BLUE,COLOR_BLACK);

	mainLen = std::ceil(static_cast<float>(LINES) / 3.0f * 2);
	infoLen = std::floor(static_cast<float>(LINES) / 3.0f); 
	mainW = subwin(stdscr,mainLen,COLS,0,0);
	infoW = subwin(stdscr,infoLen,
			COLS,mainLen,0);	
	std::atexit([]{
		delwin(mainW);
		delwin(infoW);
		endwin();		
	});

	Choice choice = Choice::Menu;
	while(choice != Choice::Exit){
		switch(choice){
		case Choice::Menu:
			choice = page_menu();
			break;
		case Choice::Open:
			choice = page_open();
			break;
		case Choice::Write:
			choice = page_write();
			break;
		}
	}  

	return 0;
}
