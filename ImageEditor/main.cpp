#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ImageHolder.hpp"

using namespace std;

void DrawMenus(sf::RenderWindow &window, ImageHolder *imageHolder){
    sf::RectangleShape sideBoxes;
    
    sideBoxes.setFillColor(sf::Color(25, 25, 25));
    
    float sideBoxesWidth = 500;
    
    sideBoxes.setSize(sf::Vector2f(sideBoxesWidth, window.getSize().y));
    window.draw(sideBoxes);
    
    sideBoxes.setPosition(window.getSize().x - sideBoxesWidth, 0);
    window.draw(sideBoxes);
}

void DrawImages(sf::RenderWindow &window, ImageHolder *imageHolder){
    for(int i = 0; i < imageHolder->layers.size(); i++){
        window.draw(imageHolder->layers.at(i)->sprite);
    }
}

int main(int argc, char const** argv)
{
    
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    
    bool rToggle = false;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Image Editor");
    
    ImageHolder *imageHolder = new ImageHolder();
    imageHolder->AddLayer("EXAMPLE_extracredit.tga");
    imageHolder->layers.at(0)->sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    imageHolder->AddLayer("icon.png");
    imageHolder->layers.at(1)->sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    
    window.setVerticalSyncEnabled(true);
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            
            if(event.type == sf::Event::Closed){
                window.close();
                cout << "closing" << endl;
            }
            
            else if(event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                for(int i = 0; i < imageHolder->layers.size(); i++)
                    imageHolder->layers.at(i)->sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()){
                
                sf::Vector2i mousePos = sf::Mouse::getPosition();
                
                    cout << mousePos.x << endl;
                    cout << mousePos.y << endl;
                
                if(imageHolder->layers.at(imageHolder->layers.size() - 1)->sprite.getLocalBounds().contains(mousePos.x, mousePos.y)){
                    cout << "meep" << endl;
                }
            }
            
            else if(event.type == sf::Event::MouseButtonPressed){
                
            }
            
            window.clear();
            
            //Image Drawing
            DrawImages(window, imageHolder);
            
            //Menu Drawing
            DrawMenus(window, imageHolder);
            
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
