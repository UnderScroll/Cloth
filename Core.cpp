#include "Core.h"
#include <algorithm>
#include <cmath>
#include <vector>

sf::View view;

void Core::run()
{
    setup();
    while (window.isOpen())
    {
        input();
        for (unsigned int i = 0; i < ups; i++)
        {
            update();
        }
        draw();
    }
}

void Core::setup()
{ 
    view = window.getDefaultView();
    view.setSize({ 500, -500.0 });
    view.setCenter({ 0,0 });
    view.move({ 100, -100 });
    window.setView(view);
    nodes.resize(cols * rows);
    
    for (unsigned int i = 0; i < cols; i++)
    {
        for (unsigned int j = 0; j < rows; j++)
        {
            /*
            if (i == 0 && j == rows-1 || i == cols - 1 && j == rows - 1)
            {
                nodes[j + i * rows] = Node(sf::Vector2f(i * 50, j * 50), true);
            }
            */
            /*
            if (i == 0 && j == 0 || i == cols - 1 && j == 0)
            {
                nodes[j + i * rows] = Node(sf::Vector2f(i * 50, j * 50), true);
            }
            */
            if (j == 0)
            {
                nodes[j + i * rows] = Node(sf::Vector2f(i * 10, j * 10), true);
            }
            else
            {
                nodes[j + i * rows] = Node(sf::Vector2f(i * 10, j * 10), false);
            }
            
        }
    }

    //horizontal
    std::cout << "Horizontal : " << (cols - 1) * rows << " elements\n";
    for (unsigned int i = 0; i < (cols-1) * rows; i++)
    {
        //std::cout << i << "->" << i + rows << std::endl;
        springs.push_back(Spring(nodes[i], nodes[i + rows]));
    }
    std::cout << "Vector size : " << springs.size() << std::endl;

    //vertical
    std::cout << "Vertical : " << cols * (rows - 1) << " elements\n";
    for (unsigned int i = 0; i < cols; i++)
    {
        for (unsigned int j = 0; j < rows - 1; j++)
        {
            //std::cout << i * rows + j << "->" << i * rows + j + 1 << std::endl;
            springs.push_back(Spring(nodes[i * rows + j], nodes[i * rows + j + 1]));
        }
    }
    std::cout << "Vector size : " << springs.size() << std::endl;
    /*
    //diagonal
    std::cout << "Diagonal : " << (cols - 1) * (rows-1) << " elements\n";
    for (unsigned int i = 0; i < cols - 1; i++)
    {
        for (unsigned int j = 0; j < rows - 1; j++)
        {
            std::cout << i * rows + j << "->" << (i+1) * rows + j + 1 << std::endl;
            springs.push_back(Spring(nodes[i * rows + j], nodes[(i + 1) * rows + j + 1]));
        }
    }

    for (unsigned int i = 0; i < cols - 1; i++)
    {
        for (unsigned int j = 0; j < rows - 1; j++)
        {
            std::cout << i * rows + j << "->" << (i + 1) * rows + j + 1 << std::endl;
            springs.push_back(Spring(nodes[i * rows + j + 1], nodes[(i + 1) * rows + j]));
        }
    }
    */
    

    std::cout << "Vector size : " << springs.size() << std::endl;
}

void Core::input()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            {
                Node* selected_node = nullptr;
                float distance = 99999;
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (Node& n : nodes)
                {
                    float mnDist = Core::distance(mousePos, n.pos);
                    if (mnDist < distance)
                    {
                        distance = mnDist;
                        selected_node = &n;
                    }
                }
                if (distance < 100)
                    selected_node->select();
            }
            break;
        case sf::Event::MouseButtonReleased:
            for (Node& n : nodes)
            {
                if (n.selected)
                    n.deselect();
            }
            break;
        }
    }
}

void Core::update()
{
    for (Spring& s : springs)
    {
        s.update();
    }

    for (Node& n : nodes)
    {
        n.update(window);
    }
    
    //system("cls");
    //std::cout << "\r[NODE] pos:(" << node0.getPos().x << "," << node0.getPos().y << ") - vel:(" << node0.getVel().x << "," << node0.getVel().y << ")\t[NODE] pos:(" << node1.getPos().x << ", " << node1.getPos().y << ") - vel : (" << node1.getVel().x << ", " << node1.getVel().y << ")        ";
}

void Core::draw()
{
    window.clear();
    
    for (Spring s : springs)
    {
        s.draw(window);
    }

    for (Node n : nodes)
    {
        n.draw(window);
    }
    
    window.display();
}

void Core::clamp(float& value, float min, float max)
{
    value = std::max(std::min(value, max), min);
}

void Core::clamp(sf::Vector2f& vector, float min_mag, float max_mag)
{
    float mag = length(sf::Vector2f(vector.x, vector.y));
    clamp(mag, min_mag, max_mag);

    setMag(vector, mag);
}

float Core::length(sf::Vector2f vector)
{
    return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float Core::distance(sf::Vector2f pointA, sf::Vector2f pointB)
{
    return (float)sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2));
}

void Core::setMag(sf::Vector2f& vector, float magnetude)
{
    float starting_mag = length(sf::Vector2f(vector.x, vector.y));
    if (starting_mag != 0)
    {
        vector = vector * (magnetude / starting_mag);
    }   
}