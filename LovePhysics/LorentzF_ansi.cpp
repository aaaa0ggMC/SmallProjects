/**@author aaaa0ggmc
 * @copyright  Copyright(c)2025
 * @date 2025/5/24
 * @description ��������ģ�⣬���������ܿ�15��
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

///���ڴ�С
constexpr int width = 800,height = 600;
//QAQ sfml�ƺ��Ա���������֧�ֲ���ô�ã�����ʹ��constexpr�ᱨ�����ˣ����ȫ�ֱ���Ҳ���ǲ���
//СС�Ƹ���
sf::Vector2f movVec = 0.003f * sf::Vector2f(static_cast<float>(width),static_cast<float>(height));
//�ų�����
constexpr double k = 0.1;
//֡��
constexpr int frame_limit = 360;
//�����ΰ뾶
constexpr double a_R = 200;
constexpr double pi = std::numbers::pi;
using vec2d = sf::Vector2<double>;

//�ж�һ�����Ƿ��ڱ߳�ΪRR��������������
bool inFn(sf::Vector2<double> pos,double RR){
	double len2 = pos.x * pos.x + pos.y * pos.y;
	double len = std::sqrt((double)len2);
	double cosv = pos.x / len;
	//����������Ƕ�
	double angle = std::acos(cosv);
	//��������һ���������εĽǶ�
	double rth = angle - (int)(angle * 3 / pi) * pi / 3.0;
	//ʹ�����Ҷ������߳�
	double d = RR * std::sqrt(3.0) / 2 / std::sin(rth + pi / 3.0);
	//std::cout << cosv << std::endl;
	//�ж��Ƿ��ڴų���
	if(d*d >= len2)return true;
	return false;
}


struct Ball{
	sf::Vector2<double> position {0,0};
	sf::Vector2<double> velocity {0,0};
	///����ļ��ʱ��
	double deltaT { 0.1 };
	double R { 1 };
	
	void updateStatus(){
       		bool in = inFn(position,a_R);
		//������ٶ� -----------  v= R * qb/m   a = v * qb/m  ��� v = kR;a = kv = k^2 R
		vec2d a = (in?1:-1) * k * vec2d(velocity.y,-velocity.x);
		position += velocity * deltaT;
		velocity += a * deltaT;		
	}
};

int main(int argc,char * arg[]){
	//Բ�ܰ뾶
	float R = (argc < 2)?(a_R / 4):(std::atof(arg[1]));
	//������������
	float scale = (argc < 3)?(1.0f):(std::atof(arg[2]));
	//deltaT��������
	float time_scale = (argc < 4)?(1.0f):(std::atof(arg[3]));
	//�Ƿ��ڿ��������ʱֹͣ
	int end_when_near = (argc < 5)?(0):(std::atoi(arg[4]));
	//���׼�����ڼ����������Ƿ񿿽�
	float error = (argc < 6)?(0.02f):(std::atof(arg[5]));
	//�ٶȽǶ�
	int angle_deg = (argc < 7)?(-90):(std::atof(arg[6]));
	//�Ƿ�ʵʱ����
	int realtime_calc = (argc < 8)?(0):(std::atoi(arg[7]));
	float start_x = (argc < 9)?(0):(std::atof(arg[8]));
	float start_y = (argc < 10)?(0.5 * std::sqrt(3.0) * a_R):(std::atof(arg[9]));
	bool calcing = true;

	std::cout << "Tips: Enter \"llz help\" for help. С��ʿ:���� llz help ��ȡ������" << std::endl;
	std::cout << "Use WASD to move, =(+) -(_) or + - to scale,space to pause/play\nWASD�ƶ� =(+0 -(_)���� + - ���š�" << std::endl;

	double scaling = 1.0f;
	//tutor and ... ads
	if(argc >= 2 && !(std::isdigit(arg[1][0]) || arg[1][0] == '-' || arg[1][0] == '+')){
		std::cout << "[English]Don't know how to use it??Now I'm gotta instruct u in ... a nerdy way..." << std::endl;
		std::cout << "llz [[optional]rotating_radius:100 equals to 1*L,half of the regular shape's length,def 50] [[optional]points to scale: this filed * 58*10^6,def 1.0] [[optional]deltaT scale:this field * 0.00001 or 0.01 if it's realtime mode,def 1.0] [end calc when near the original position,0 no,other yes,def 0] [[optional]error: the length to detect whether a point is near to the other,paired with end calc,def 0.02] [[optional]velocity angle: in degress,def -90, towards the bottom of your screen] [[optional]realtime calc?:calculate the points in realtime,which means better visual effects but less precision] [[optional]start x:def 0][[optional]start y : def sqrt(3)/2 * L]" << std::endl;
		std::cout << "[Chinese]��֪����ôʹ�ã��������Ҿ�Ҫ���......��������һ���ؽ�����......" << std::endl;
		std::cout << "llz [[��ѡ�����涼�ǿ�ѡ�����ñ���]��ת�뾶:100��ζ�����������Ŀ���L,Ĭ�� 50�������Ǹ����㷢���ͼ��] [����ĵ����������ֵ:Ĭ��Ϊ1.0,���Ԥ�ȼ���ĵ������Ϊ 58*10^6 * ����ֶΣ�����㿪��ʵʱģʽ�����û��] [deltaT����ֵ��deltaTΪ0.00001(�����ʵʱģʽ��Ϊ0.01)��Ĭ��1.0,����ᵼ�¾����½�����С�ᵼ��������������������С] [�Ƿ��Զ�ֹͣ�����Ϊ��0������ᵱ��ǰλ�ÿ������λ��ʱ��Ϊ�ﵽԭ����ֹ����] [���ֵ�������Զ���ֹ����ʾ�㵽���λ�õı��ж�Ϊ�����������,Ĭ��0.02] [�ٶȽǶȣ��Ƕ��ƣ�Ĭ��-90,����Ŀ�еķ���] [ʵʱģʽ��Ĭ��Ϊ0����������0�����󲻻�Ԥ��������㣬���ӻ�Ч����һ��] [��ʼʱx���꣬Ĭ��0] [��ʼʱy���꣬Ĭ�� ����3����2����L(L����100) ]" << std::endl;
		std::cout << "Examples(����):\n" << "llz 50 \n llz 100 1 1 1 0 0 -90 1" << std::endl;
		std::cout << "Created by aaaa0ggmc(Blog: https://yslwd.eu.org)\nThank u for using it.\naaaa0ggmc(���˲��� https://yslwd.eu.org)����\n��л���ʹ�á�" << std::endl;
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
		//Ԥ�ȼ������
		std::cout << "Gosh,you choose to pre-gen the points.Now wait and see ... the progress." << std::endl;
		vec2d stpos = lt.position;
		int64_t count = 58*1e6 * scale;
		//���ض����ĵ������*5
		int dots = 0;
		for(int64_t i = 0;i < count;i++){
			//���
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
				//�򵥵ļ��ض���
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

