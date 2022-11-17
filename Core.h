#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Node.h"
#include "Spring.h"

const double timestep = 5.0e-2;
const int ups = floor(1 / timestep);
const sf::Vector2f gravity = sf::Vector2f( 0.0f, -9.81f );


class Core
{
public:
	Core(sf::RenderWindow& render_window) : window(render_window) {};
	void run();
	static const unsigned int rows = 10;
	static const unsigned int cols = 20;

	static void clamp(float& value, float min, float max);
	static void clamp(sf::Vector2f& value, float min_mag, float max_mag);
	static void setMag(sf::Vector2f& vector, float magnetude);
	static float length(sf::Vector2f vector);
	static float distance(sf::Vector2f pointA, sf::Vector2f pointB);

private:
	sf::RenderWindow& window;
	
	std::vector<Node> nodes;
	std::vector<Spring> springs;

	void setup();
	void input();
	void update();
	void draw();
};