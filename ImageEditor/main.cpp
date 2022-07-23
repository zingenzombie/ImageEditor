#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Image.hpp"

using namespace std;

int main(int argc, char const** argv)
{
    
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    
    bool rToggle = false;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Image Editor");
    
    window.setVerticalSyncEnabled(true);
    
    sf::Image image;
    image.loadFromFile("car.tga");
    sf::Texture imageTxt;
    imageTxt.loadFromImage(image);
    sf::Sprite imageSpr;
    imageSpr.setTexture(imageTxt);
    imageSpr.setOrigin(image.getSize().x / 2, image.getSize().y / 2);
    
    imageSpr.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                cout << "closing" << endl;
            }
            
            //Keyboard toggles
            if (event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                    rToggle = !rToggle;
            }
            
                
            //Mouse movement & related actions
            if (event.type == sf::Event::MouseWheelMoved){
                
                //Rotate
                if(rToggle){
                    imageSpr.rotate(event.mouseWheel.delta * 15);
                    break;
                }
                
                //Zoom
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem))
                   imageSpr.scale( 1 + (float) event.mouseWheel.delta / 10, 1 + (float) event.mouseWheel.delta / 10);
                if(imageSpr.getScale().x < .1)
                    imageSpr.setScale(.1, .1);
                
                //Scroll
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    imageSpr.move((float) event.mouseWheel.delta * -10, 0);
                else
                    imageSpr.move(0, (float) event.mouseWheel.delta * 10);
            }
            
            window.clear();
            
            window.draw(imageSpr);
            
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
