#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<string>
using namespace std;
// Classes for Dots 
class Dot{ 
    public:
    sf::CircleShape shape;
    bool active;
};
//Base Class 
class Entity{
    public:
    sf :: CircleShape shape;
    float x,y,speed;
};
// derived class for PacMan
class PacMan : public Entity{
    public:
    int lives;
};
//Derived Class for Ghost 
class Ghost : public Entity {
 public:
 float dirX, dirY;
};
//Doing MAIN
int main(){
    sf :: RenderWindow window(sf::VideoMode(800,600),"Pac-Man");
    PacMan pacman;
    pacman.lives=3;
    //PACMAN Characteristics 
    pacman.shape.setRadius(20);
    pacman.shape.setFillColor(sf::Color::Yellow);
    pacman.x=300;
    pacman.y=400;
    pacman.speed=1.5;
    //Ghost Characteristics :
    Ghost ghost;
    ghost.shape.setRadius(20);
    ghost.shape.setFillColor(sf::Color::Red);
    ghost.x=100;
    ghost.y=100;
    ghost.speed=0.08;
    ghost.dirX=1;
    ghost.dirY=1;

    int size=10;
    int score =0;
    int gameState=0;
    sf :: Font font; // FOR font
    font.loadFromFile("consola.ttf");
    //FONT Properties for score 
    sf :: Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10,10);
    //FONT Properties for LIves
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(650,10);
    //Font properties for GameOver :
    sf::Text gameOvertext;
    gameOvertext.setFont(font);
    gameOvertext.setCharacterSize(50);
    gameOvertext.setFillColor(sf::Color::Red);
    gameOvertext.setPosition(200,200);
    gameOvertext.setString("GAME OVER!!!");
    //FONT Properties for reply Text:

    //Loop for Dots 
    Dot dots[size];
    for(int i=0;i<size;i++){
        dots[i].shape.setRadius(5);
        dots[i].shape.setFillColor(sf::Color::White);
        dots[i].active=true;
        dots[i].shape.setPosition(100 + i*60,400);
    }
    // While Loop for the game to coontinue 
    while(window.isOpen()){
         sf::Event event;
         while(window.pollEvent(event)){
            if(event.type == sf:: Event :: Closed)
            window.close();
         }
         //Arrow keys movement 
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          pacman.x-=pacman.speed;//speed will control how much co-ordinates they will move fast or slower.
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          pacman.x+=pacman.speed;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          pacman.y-=pacman.speed;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          pacman.y+=pacman.speed;
          //PAcman touching walls 
          if(pacman.x<0) 
          pacman.x=0;
          if(pacman.y<0)
          pacman.y=0;
          if(pacman.x>800 - pacman.shape.getRadius()*2)
          pacman.x=800 - pacman.shape.getRadius()*2;
          if(pacman.y>600-pacman.shape.getRadius()*2)
          pacman.y=600- pacman.shape.getRadius()*2;  
           
          ghost.x+=ghost.speed*ghost.dirX;
          ghost.y+=ghost.speed*ghost.dirY;
         //  Ghost movement
         if(pacman.x>ghost.x){
            ghost.dirX=1;
         }else{
            ghost.dirX=-1;
         }
         if(pacman.y>ghost.y){
            ghost.dirY=1;
         }else{
            ghost.dirY=-1;
        }
         // Ghost maze touching logic:
         float dx = (pacman.x + pacman.shape.getRadius())-(ghost.x + ghost.shape.getRadius());
         float dy = (pacman.y + pacman.shape.getRadius())-(ghost.y + ghost.shape.getRadius());
         float distance = sqrt(dx*dx + dy*dy);
         if(distance<pacman.shape.getRadius()+ghost.shape.getRadius()){
            pacman.lives--;
            pacman.x=300;
            pacman.y=400;
            ghost.x=100;
            ghost.y=100;
         }//if lives finish terminate:
         if(pacman.lives<=0){
            gameState=1; // 1 Mean GameOver , 0 mean countinue :
         }
         
          //Loop for dots active + plus score count :
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
          //LOOP for game is coutinue or not ?
         window.clear(sf::Color::Black); // this statement is use to reset the trail of previus frames 
         if(gameState==0){          
          for(int i=0 ;i<size;i++){
            if(dots[i].active==true){
                window.draw(dots[i].shape);
             }
           }                 
         //Display code:
         pacman.shape.setPosition(pacman.x,pacman.y);
         scoreText.setString("SCORE: "+ to_string(score));
         window.draw(scoreText);
         window.draw(pacman.shape);
         ghost.shape.setPosition(ghost.x,ghost.y);
         window.draw(ghost.shape);
         livesText.setString("LIVES: "+ to_string(pacman.lives));
         window.draw(livesText);  
        }
         if (gameState==1){
        window.draw(gameOvertext);
      }  
          window.display();   
    }   
    return 0;
}