#include "Core.h"
#include "Node.h"
#include "Spring.h"

Spring::Spring(Node& a, Node& b)
	:node_a(a), node_b(b), stiffness(8.9f), damping(0.99f)
{
	baseLength = Core::distance(node_a.pos, node_b.pos);
}


void Spring::update()
{
	sf::Vector2f force = node_b.pos - node_a.pos;
	float mag = (Core::length(force) - baseLength) * stiffness;
	Core::setMag(force, mag);
	node_a.applyForce(force);
	node_a.vel.x = node_a.vel.x * damping;
	node_a.vel.y = node_a.vel.y * damping;
	force.x = -force.x;
	force.y = -force.y;
	node_b.applyForce(force);
	node_b.vel.x = node_b.vel.x * damping;
	node_b.vel.y = node_b.vel.y * damping;
}

void Spring::draw(sf::RenderWindow& window)
{
	line[0] = node_a.pos;
	line[1] = node_b.pos;
	window.draw(line, 2, sf::Lines);
}