#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class Spring
{
private:
	float baseLength;
	const float stiffness;
	const float damping;

	Node &node_a;
	Node &node_b;

	sf::Vertex line[2];

	sf::Vector2f force;
public:
	Spring(Node &a, Node &b);

	void update();
	void draw(sf::RenderWindow& window);
};