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
    image.loadFromFile("Untitled_Artwork.png");
    sf::Texture imageTxt;
    imageTxt.loadFromImage(image);
    sf::Sprite imageSpr;
    imageSpr.setTexture(imageTxt);
    imageSpr.setOrigin(image.getSize().x / 2, image.getSize().y / 2);
    
    imageSpr.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            
            if(event.type == sf::Event::Resized){
                imageSpr.setPosition(window.getSize().x / 2, window.getSize().y / 2);
                float x = window.getView().getSize().x;
                float y = window.getView().getSize().y;
                sf::Vector2u vectorTmp(x, y);
                window.setSize(vectorTmp);
            }
            
            //image.getPixel(<#unsigned int x#>, <#unsigned int y#>)
            
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
                
                /* TEMPORARILY REMOVED IN ORDER TO CREATE IMAGE MODIFICATION
                //Rotate
                if(rToggle){
                    imageSpr.rotate(event.mouseWheel.delta * 15);
                    break;
                }
                 */
                
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
            
            /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.focus){
                sf::Mouse::
            }*/
            
            window.clear();
            
            window.draw(imageSpr);
            
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
