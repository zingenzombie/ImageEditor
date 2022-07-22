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
            
            if (event.type == sf::Event::MouseWheelMoved)
            {
                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
                //imageSpr.scale(1.1, 1.1);
                imageSpr.scale( 1 +(float) event.mouseWheel.delta / 10, 1 + (float) event.mouseWheel.delta / 10);
            }
            
            window.clear();
            
            window.draw(imageSpr);
            
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
