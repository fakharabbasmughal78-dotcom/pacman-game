#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

class PacMan{
    public:
    sf::CircleShape shape;
    float x,y,speed;
};
int main(){
    sf :: RenderWindow window(sf::VideoMode(800,600),"Pac-Man");
    PacMan pacman;
    pacman.shape.setRadius(50);
    pacman.shape.setFillColor(sf::Color::Yellow);
    pacman.x=300;
    pacman.y=400;
    pacman.speed=0.1;
    pacman.shape.setPosition(pacman.x , pacman.y);

    while(window.isOpen()){
         sf::Event event;
         while(window.pollEvent(event)){
            if(event.type == sf:: Event :: Closed)
            window.close();
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          pacman.x-=pacman.speed;//speed will control how much co-ordinates they will move fast or slower.
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          pacman.x+=pacman.speed;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          pacman.y-=pacman.speed;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          pacman.y+=pacman.speed;
         window.clear(sf::Color::Black);
         pacman.shape.setPosition(pacman.x,pacman.y);
         window.draw(pacman.shape);
         window.display();
    }
    return 0;
}
