#pragma once
#include <SFML/Graphics.hpp>

class Node
{
public:
	Node();
	Node(sf::Vector2f position);
	Node(sf::Vector2f position, bool isStatic);

	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void applyForce(sf::Vector2f force);

	void select();
	void deselect();

	sf::Vector2f pos, vel;
	bool selected;
private:
	sf::CircleShape shape;
	bool isStatic = false;
};