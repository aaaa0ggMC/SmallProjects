/**@author aaaa0ggmc
 * @copyright  Copyright(c)2025
 * @date 2025/5/5
 * @description 模拟鸟类运动
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

///每一帧的模拟时间
constexpr float deltaT = 0.1f;
constexpr int width = 800,height = 600;
constexpr float influence = 100.0f;
constexpr float minDist = 100.0f;
constexpr float maxForce = 10.0f;
constexpr float maxSpeed = 10.0f;
constexpr float mf = 0.001f;

sf::Vector2f movVec = 0.008f * sf::Vector2f(static_cast<float>(width),static_cast<float>(height));


struct Boid{
	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Color color;
	static std::mt19937 mt_engine;//梅森旋转

	void updateStatus(const std::vector<Boid> & boids){
		static constinit float inf_2 = influence * influence;
		static constinit float md_2 = minDist * minDist;

		int neighbors = 0;
		sf::Vector2f sep {0,0},align {0,0},cohen {0,0};

		for(auto & bd : boids){
			sf::Vector2f dist = position - bd.position;
			float d_2 = dist.x*dist.x + dist.y*dist.y;

			if(d_2 <= inf_2){
				neighbors ++;
				if(d_2 <= md_2){
					sep += dist / std::max(d_2,mf*mf);
				}
				align += bd.velocity;
				cohen += bd.position;
			}
		}

		if(neighbors > 0){
       			align /= float(neighbors);
       			cohen /= float(neighbors);
        		cohen -= position;
		}

		std::uniform_real_distribution<float> velo (-2.0f,2.0f);
		sf::Vector2f acc = sep * 40.f + align * 0.01f + cohen * 0.05f + sf::Vector2f(velo(mt_engine),velo(mt_engine)) ;
		float len_2 = acc.x * acc.x + acc.y * acc.y;
		if(len_2 > maxForce * maxForce)acc *= maxForce / std::sqrt(len_2);
		velocity += acc * deltaT;
		float vlen_2 = velocity.x * velocity.x + velocity.y * velocity.y;
		if(vlen_2 > maxSpeed * maxSpeed)velocity *= maxSpeed / std::sqrt(vlen_2);
	}

	void postUpdate(){
		position += velocity * deltaT;
	}
};
std::mt19937 Boid::mt_engine (std::random_device{}());//梅森旋转

int main(int argc,char * arg[]){
	int boid_count = (argc < 2)?(10):(std::atoi(arg[1]));
	sf::RenderWindow window (sf::VideoMode(width,height),"HelloBoids.");
	sf::View myView (sf::FloatRect(0,0,width,height));
	std::vector<Boid> boids;

	window.setFramerateLimit(240);
	//随机数引擎
	std::mt19937 mt_engine (std::random_device{}());//梅森旋转
	std::uniform_int_distribution dist (0,width * height);//全局分布
	
	//init planets
	for(int64_t i = 0;i < boid_count;++i){
		std::uniform_int_distribution<unsigned int> ugen(100,255);
		std::uniform_real_distribution<float> velo (-2.0f,2.0f);
		Boid b;
		b.position = {static_cast<float>(dist(mt_engine) % width),static_cast<float>(dist(mt_engine) % height)};
		b.color = sf::Color(ugen(mt_engine),ugen(mt_engine),ugen(mt_engine));
		b.velocity = {velo(mt_engine),velo(mt_engine)};

		boids.push_back(b);
	}

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
		for(auto & ct : boids){
			sf::CircleShape p (20.0f , 3);
			p.setPosition(ct.position);
			p.setFillColor(ct.color);
			p.setRotation(std::atan2(ct.velocity.y, ct.velocity.x) * 180.0f / std::numbers::pi_v<float>);
			window.draw(p);
			//更新
			ct.updateStatus(boids);
		}
		for(auto & ct : boids){
			ct.postUpdate();
		}
		window.display();
	}
	return 0;
}

