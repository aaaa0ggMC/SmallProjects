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

constexpr int width = 800,height = 600;
//QAQ sfml似乎对编译期运算支持不怎么好，这里使用constexpr会报错，算了，多个全局变量也不是不行
//小小破个戒
sf::Vector2f movVec = 0.0006f * sf::Vector2f(static_cast<float>(width),static_cast<float>(height));
//磁场常数
constexpr double k = 0.1;
constexpr int frame_limit = 360;
constexpr double a_R = 200;
constexpr double pi = std::numbers::pi;
using vec2d = sf::Vector2<double>;

bool inFn(sf::Vector2<double> pos,double RR){
	double len2 = pos.x * pos.x + pos.y * pos.y;
	double len = std::sqrt((double)len2);
	double cosv = pos.x / len;
	double angle = std::acos(cosv);
	double pi = std::numbers::pi;

	double rth = angle - (int)(angle * 3 / pi) * pi / 3.0;

	double d = RR * std::sqrt(3.0) / 2 / std::sin(rth + pi / 3.0);

	//std::cout << cosv << std::endl;
	if(d*d >= len2)return true;
	return false;
}


struct Ball{
	sf::Vector2<double> position {0,0};
	sf::Vector2<double> velocity {0,0};

	double deltaT { 0.1 };
	
	void updateStatus(){
       		bool in = inFn(position,a_R);
		vec2d a = (in?1:-1) * k * vec2d(velocity.y,-velocity.x);
		position += velocity * deltaT;
		velocity += a * deltaT;		
	}
};

int main(int argc,char * arg[]){
	float R = (argc < 2)?(a_R / 2):(std::atof(arg[1]));
	double deltaT = 0.00001;
	int64_t index = 0;
	sf::VertexArray vs(sf::LineStrip,0);
	{
		Ball lt;
		lt.position.y = -1 *0.5 * std::sqrt(3.0) * a_R;
		lt.velocity.y = k * R;
		lt.deltaT = deltaT;
		int64_t count = 58*1e6;
		for(int64_t i = 0;i < count;i++){
			if(i % (int64_t)10000 == 0){
				sf::Vertex vx;
				vx.position = sf::Vector2f((float)lt.position.x,(float)lt.position.y) 
					+ sf::Vector2f(width/2,height/2);
				vx.color = sf::Color(255,255,255);
				vs.append(vx);
			}

			lt.updateStatus();
			if(i % (int64_t)1e6 == 0){
				static int dices = 0;
				std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
				std::cout << "Loading "  << i << "/" << count;
				++dices;
				for(int i = 0;i < dices/3;++i)std::cout << ".";
				if(dices >= 9)dices = 0;
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
			myView.move(0,-movVec.y);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			myView.move(0,movVec.y);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			myView.move(-movVec.x,0);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			myView.move(movVec.x,0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)){
			myView.zoom(1.01f);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
			myView.zoom(1.0f / 1.01f);
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
			ball.setPosition(vs[index].position);
			index++;
			if(index >= vs.getVertexCount())index = 0;
			window.draw(ball);
		}
		window.draw(vs);
		window.display();
	}
	return 0;
}


