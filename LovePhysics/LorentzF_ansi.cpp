/**@author aaaa0ggmc
 * @copyright  Copyright(c)2025
 * @date 2025/5/24
 * @description 洛伦兹力模拟，用于物理周考15题
 **/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdint.h>
#include <unordered_map>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <cstring>
#include <numbers>
#include <cctype>

///窗口大小
constexpr int width = 800,height = 600;
//QAQ sfml似乎对编译期运算支持不怎么好，这里使用constexpr会报错，算了，多个全局变量也不是不行
//小小破个戒
sf::Vector2f movVec = 0.003f * sf::Vector2f(static_cast<float>(width),static_cast<float>(height));
//磁场常数
constexpr double k = 0.1;
//帧率
constexpr int frame_limit = 360;
//六边形半径
constexpr double a_R = 200;
constexpr double pi = std::numbers::pi;
using vec2d = sf::Vector2<double>;

//判断一个点是否在边长为RR的正六边形里面
bool inFn(sf::Vector2<double> pos,double RR){
	double len2 = pos.x * pos.x + pos.y * pos.y;
	double len = std::sqrt((double)len2);
	double cosv = pos.x / len;
	//反余弦算出角度
	double angle = std::acos(cosv);
	//算出相对于一个正三角形的角度
	double rth = angle - (int)(angle * 3 / pi) * pi / 3.0;
	//使用正弦定理计算边长
	double d = RR * std::sqrt(3.0) / 2 / std::sin(rth + pi / 3.0);
	//std::cout << cosv << std::endl;
	//判断是否在磁场中
	if(d*d >= len2)return true;
	return false;
}


struct Ball{
	sf::Vector2<double> position {0,0};
	sf::Vector2<double> velocity {0,0};
	///计算的间隔时间
	double deltaT { 0.1 };
	double R { 1 };
	
	void updateStatus(){
       		bool in = inFn(position,a_R);
		//计算加速度 -----------  v= R * qb/m   a = v * qb/m  因此 v = kR;a = kv = k^2 R
		vec2d a = (in?1:-1) * k * vec2d(velocity.y,-velocity.x);
		position += velocity * deltaT;
		velocity += a * deltaT;		
	}
};

int main(int argc,char * arg[]){
	//圆周半径
	float R = (argc < 2)?(a_R / 4):(std::atof(arg[1]));
	//点数放缩比例
	float scale = (argc < 3)?(1.0f):(std::atof(arg[2]));
	//deltaT放缩比例
	float time_scale = (argc < 4)?(1.0f):(std::atof(arg[3]));
	//是否在靠近最初点时停止
	int end_when_near = (argc < 5)?(0):(std::atoi(arg[4]));
	//误差准许，用于检测与最初点是否靠近
	float error = (argc < 6)?(0.02f):(std::atof(arg[5]));
	//速度角度
	int angle_deg = (argc < 7)?(-90):(std::atof(arg[6]));
	//是否实时运算
	int realtime_calc = (argc < 8)?(0):(std::atoi(arg[7]));
	float start_x = (argc < 9)?(0):(std::atof(arg[8]));
	float start_y = (argc < 10)?(0.5 * std::sqrt(3.0) * a_R):(std::atof(arg[9]));
	bool calcing = true;

	std::cout << "Tips: Enter \"llz help\" for help. 小贴士:输入 llz help 获取帮助。" << std::endl;
	std::cout << "Use WASD to move, =(+) -(_) or + - to scale,space to pause/play\nWASD移动 =(+0 -(_)或者 + - 缩放。" << std::endl;

	double scaling = 1.0f;
	//tutor and ... ads
	if(argc >= 2 && !(std::isdigit(arg[1][0]) || arg[1][0] == '-' || arg[1][0] == '+')){
		std::cout << "[English]Don't know how to use it??Now I'm gotta instruct u in ... a nerdy way..." << std::endl;
		std::cout << "llz [[optional]rotating_radius:100 equals to 1*L,half of the regular shape's length,def 50] [[optional]points to scale: this filed * 58*10^6,def 1.0] [[optional]deltaT scale:this field * 0.00001 or 0.01 if it's realtime mode,def 1.0] [end calc when near the original position,0 no,other yes,def 0] [[optional]error: the length to detect whether a point is near to the other,paired with end calc,def 0.02] [[optional]velocity angle: in degress,def -90, towards the bottom of your screen] [[optional]realtime calc?:calculate the points in realtime,which means better visual effects but less precision] [[optional]start x:def 0][[optional]start y : def sqrt(3)/2 * L]" << std::endl;
		std::cout << "[Chinese]不知道怎么使用？？现在我就要像个......像个书呆子一样地教你了......" << std::endl;
		std::cout << "llz [[可选，后面都是可选，懒得标了]旋转半径:100意味着这个物理题目里的L,默认 50，就是那个让你发狂的图像] [计算的点的数量缩放值:默认为1.0,最后预先计算的点的数量为 58*10^6 * 这个字段，如果你开了实时模式那这个没用] [deltaT缩放值，deltaT为0.00001(如果在实时模式下为0.01)，默认1.0,调大会导致精度下降，调小会导致运算量增大，运算距离减小] [是否自动停止：如果为非0，程序会当当前位置靠近最初位置时视为达到原点终止计算] [误差值：用于自动终止，表示点到最初位置的被判定为到点的最大距离,默认0.02] [速度角度，角度制，默认-90,即题目中的方向] [实时模式，默认为0不开启，非0开启后不会预先运算出点，可视化效果好一点] [开始时x坐标，默认0] [开始时y坐标，默认 根号3除以2乘上L(L等于100) ]" << std::endl;
		std::cout << "Examples(例子):\n" << "llz 50 \n llz 100 1 1 1 0 0 -90 1" << std::endl;
		std::cout << "Created by aaaa0ggmc(Blog: https://yslwd.eu.org)\nThank u for using it.\naaaa0ggmc(个人博客 https://yslwd.eu.org)制作\n感谢你的使用。" << std::endl;
		return 520;
	}

	double deltaT = (realtime_calc?0.01:0.00001) * time_scale;
	int64_t index = 0;
	sf::Clock elapse;
	sf::VertexArray vs(sf::LineStrip,0);
	Ball lt;
	lt.position.x = start_x;
	lt.position.y = -start_y;
	lt.velocity.y = k * R * sin(-angle_deg / 360.0 * 2 * pi);
	lt.velocity.x = k * R * cos(angle_deg / 360.0 * 2 * pi);
	lt.R = R;
	lt.deltaT = deltaT;
	if(!realtime_calc){
		//预先计算点们
		std::cout << "Gosh,you choose to pre-gen the points.Now wait and see ... the progress." << std::endl;
		vec2d stpos = lt.position;
		int64_t count = 58*1e6 * scale;
		//加载动画的点的数量*5
		int dots = 0;
		for(int64_t i = 0;i < count;i++){
			//插点
			if((int64_t)(i * time_scale) % (int64_t)(4 * 1e4) == 0){
				sf::Vertex vx;
				vx.position = sf::Vector2f((float)lt.position.x,(float)lt.position.y) 
					+ sf::Vector2f(width/2,height/2);
				vx.color = sf::Color(255,255,255);
				vs.append(vx);
				if(end_when_near && i >= count/4){
					vec2d minus = lt.position - stpos;
					if((minus.x*minus.x + minus.y*minus.y) <= R * R * error){
						std::cout << "\nThe ball has returned to the origin.So I need to guandiao." << std::endl;
						//make a shift	
						vx.position = sf::Vector2f((float)stpos.x,(float)stpos.y) 
							+ sf::Vector2f(width/2,height/2);
						vs.append(vx);
						break;
					}
				}
			}

			lt.updateStatus();
			if(i % (int64_t)1e6 == 0){
				//简单的加载动画
				std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
				std::cout << "Loading "  << i << "/" << count;
				++dots;
				for(int i = 0;i < dots/5;++i)std::cout << ".";
				if(dots >= 20)dots = 0;
				std::cout.flush();
			}
		}
	}

	sf::RenderWindow window(sf::VideoMode(width,height),"LorentzForce");
	sf::View myView(sf::FloatRect(0,0,width,height));
	window.setFramerateLimit(frame_limit);
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)window.close();
		}
		window.setView(myView);
		window.clear(sf::Color(0,0,0));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			myView.move(0,-movVec.y * scaling);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			myView.move(0,movVec.y * scaling);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			myView.move(-movVec.x * scaling,0);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			myView.move(movVec.x * scaling,0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
			myView.zoom(1.01f);
			scaling *= 1.01f;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
			myView.zoom(1.0f / 1.01f);
			scaling /= 1.01f;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapse.getElapsedTime().asMilliseconds() >= 400){
			calcing = !calcing;
			elapse.restart();
		}
		
		if(calcing && realtime_calc){
			lt.updateStatus();
			sf::Vertex vx;
			vx.position = sf::Vector2f((float)lt.position.x,(float)lt.position.y) 
				+ sf::Vector2f(width/2,height/2);
			vx.color = sf::Color(255,255,255);
			vs.append(vx);
		}

		//Draw phase
		{
			sf::CircleShape ss (a_R,6);
			ss.setOrigin(a_R,a_R);
			ss.setPosition(width / 2,height /2);
			ss.setFillColor(sf::Color(155,155,255,100));
			ss.setRotation(90);
			window.draw(ss);
		}

		//Balls
		{
			sf::CircleShape ball(10);
			ball.setFillColor(sf::Color(255,255,0));
			ball.setOrigin(5,5);
			
			if(realtime_calc){
				ball.setPosition(lt.position.x + width/2,lt.position.y + height/2);
			}else{
				ball.setPosition(vs[index].position);
				if(calcing){
					index++;
				}
				if(index >= vs.getVertexCount())index = 0;
			}
			window.draw(ball);
		}
		window.draw(vs);
		window.display();
	}
	return 0;
}

