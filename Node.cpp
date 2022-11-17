#include "Node.h"
#include "Core.h"
#include <assert.h>

Node::Node()
	:pos(sf::Vector2f(0,0)), selected(false)
{
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(pos);
	shape.setRadius(4);
	shape.setOrigin({shape.getRadius(),shape.getRadius() });
}

Node::Node(sf::Vector2f position)
	:pos(position), selected(false)
{
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(pos);
	shape.setRadius(4);
	shape.setOrigin({ shape.getRadius(),shape.getRadius() });
}

Node::Node(sf::Vector2f position, bool isStatic)
	:pos(position), isStatic(isStatic), selected(false)
{
	if (isStatic)
	{
		shape.setFillColor(sf::Color::Blue);
	}
	else
	{
		shape.setFillColor(sf::Color::Red);
	}
	
	shape.setPosition(pos);
	shape.setRadius(4);
	shape.setOrigin({ shape.getRadius(),shape.getRadius() });
}

void Node::draw(sf::RenderWindow& window)
{
	window.draw(this->shape);
}

void Node::update(sf::RenderWindow& window)
{
	if (!isStatic)
	{
		if (selected)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			sf::Vector2f force = sf::Vector2f(mousePos.x - pos.x, mousePos.y - pos.y);
			applyForce(force);
		}
		applyForce(gravity);
		Core::clamp(vel, -50.0f, 50.0f);
		pos += sf::Vector2f(vel.x * (float)timestep, vel.y * (float)timestep);
		shape.setPosition(pos);
	}
}

void Node::applyForce(sf::Vector2f force)
{
	vel += sf::Vector2f(force.x * (float)timestep, force.y * (float)timestep);
}

void Node::select()
{
	selected = true;
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Green);
}

void Node::deselect()
{
	selected = false;
	shape.setOutlineThickness(0);
}