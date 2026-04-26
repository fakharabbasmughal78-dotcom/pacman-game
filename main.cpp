#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<string>
using namespace std;
class Dot{
    public:
    sf::CircleShape shape;
    bool active;
};

class PacMan{
    public:
    sf::CircleShape shape;
    float x,y,speed;
};
int main(){
    sf :: RenderWindow window(sf::VideoMode(800,600),"Pac-Man");
    PacMan pacman;
    
    pacman.shape.setRadius(20);
    pacman.shape.setFillColor(sf::Color::Red);
    pacman.x=300;
    pacman.y=400;
    pacman.speed=1.3;

    int size=10;
    int score =0;
    sf :: Font font;
    font.loadFromFile("consola.ttf");

    sf :: Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10,10);

    Dot dots[size];
    for(int i=0;i<size;i++){
        dots[i].shape.setRadius(5);
        dots[i].shape.setFillColor(sf::Color::White);
        dots[i].active=true;
        dots[i].shape.setPosition(100 + i*60,400);
    }
     
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
          if(pacman.x<0) 
          pacman.x=0;
          if(pacman.y<0)
          pacman.y=0;
          if(pacman.x>800 - pacman.shape.getRadius()*2)
          pacman.x=800 - pacman.shape.getRadius()*2;
          if(pacman.y>600-pacman.shape.getRadius()*2)
          pacman.y=600- pacman.shape.getRadius()*2;  

          for(int i=0;i<size;i++){
            if(dots[i].active){
                float dx=(pacman.x+pacman.shape.getRadius()) - dots[i].shape.getPosition().x;
                float dy=(pacman.y+pacman.shape.getRadius()) - dots[i].shape.getPosition().y;
                float distance = sqrt(dx*dx + dy*dy);
                if(distance<pacman.shape.getRadius()){  // half radius will now make it stciker like to eat the whole dot
                    dots[i].active=false;
                    score++;
                }
            }
          }
         window.clear(sf::Color::Black);
         
         for(int i=0 ;i<size;i++){
            if(dots[i].active==true){
                window.draw(dots[i].shape);
            }
         }
         pacman.shape.setPosition(pacman.x,pacman.y);
         scoreText.setString("SCORE: "+ to_string(score));
         window.draw(scoreText);
         window.draw(pacman.shape);
         window.display();
    }
    return 0;
}
// we was trying to create task.json
// beacuse in this we have to eneter 3 commoneds 
//cntrl+shft+b didnot work but score wokred with 3 commandds
// didnot push the score command till now due to electricity.