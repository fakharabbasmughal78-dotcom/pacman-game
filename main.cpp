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
    pacman.x=400;
    pacman.y=300;
    pacman.speed=0.1;
    pacman.shape.setPosition(pacman.x , pacman.y);

    while(window.isOpen()){
         sf::Event event;
         while(window.pollEvent(event)){
            if(event.type == sf:: Event :: Closed)
            window.close();
         }
         window.clear(sf::Color::Black);
         window.draw(pacman.shape);
         window.display();
    }
    return 0;
}
