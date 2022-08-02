#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ImageHolder.hpp"
#include "Buttons.hpp"

using namespace std;

void DrawMenus(sf::RenderWindow &window, ImageHolder *imageHolder, Buttons *buttons){
    sf::RectangleShape sideBoxes;
    
    sideBoxes.setFillColor(sf::Color(25, 25, 25));
    
    float sideBoxesWidth = 500;
    
    sideBoxes.setSize(sf::Vector2f(sideBoxesWidth, window.getSize().y));
    window.draw(sideBoxes);
    
    sideBoxes.setPosition(window.getSize().x - sideBoxesWidth, 0);
    window.draw(sideBoxes);
    
    for(int i = 0; i < buttons->buttons.size(); i++){
        window.draw(buttons->buttons.at(i)->rectangle);
    }
}

void TestFunctionA(){
    cout << "A!!!" << endl;
}

void TestFunctionB(){
    cout << "B!!!" << endl;
}

void TestFunctionC(){
    cout << "C!!!" << endl;
}

void TestFunctionD(){
    cout << "D!!!" << endl;
}

void LayerSelect(ImageHolder *imageHolder, Buttons::Button button, int i){
    imageHolder->activeImage = i;
}

Buttons *CreateButtons(sf::RenderWindow &window, ImageHolder *imageHolder){
    Buttons *buttons = new Buttons();
    
    for(int i = 0; i < imageHolder->layers.size(); i++)
        buttons->AddButton(sf::Vector2f(450, 100), sf::Vector2i(window.getSize().x - 250, window.getSize().y - 75 - (i * 125)), sf::Color(64, 64, 64), "layer", TestFunctionA);
    
    buttons->AddButton(sf::Vector2f(450, 100), sf::Vector2i(250, 75), sf::Color(64, 64, 64), "These Are Words", TestFunctionA);
    buttons->AddButton(sf::Vector2f(450, 100), sf::Vector2i(250, 200), sf::Color(128, 128, 128), "These Are Also Words", TestFunctionB);
    buttons->AddButton(sf::Vector2f(450, 100), sf::Vector2i(250, 325), sf::Color(192, 192, 192), "These Are Also Words", TestFunctionC);
    buttons->AddButton(sf::Vector2f(450, 100), sf::Vector2i(250, 450), sf::Color(255, 255, 255), "These Are Also Words", TestFunctionD);
    
    return buttons;
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
    
    Buttons *buttons = CreateButtons(window, imageHolder);
    
    //window.setVerticalSyncEnabled(true);
    
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
            
            if(event.type == sf::Event::MouseButtonPressed && window.hasFocus()){
                
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                for(int i = 0; i < buttons->buttons.size(); i++){
                    if(buttons->buttons.at(i)->HasBeenClicked(mousePos)){
                        if(buttons->buttons.at(i)->words == "layer"){
                            LayerSelect(imageHolder, *buttons->buttons.at(i), i);
                            break;
                        }
                        buttons->buttons.at(i)->function();
                        break;
                    }
                }
            }
            
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()){
                
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                //Image coloring
                if(imageHolder->layers.at(imageHolder->activeImage)->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                    mousePos.x = mousePos.x - imageHolder->layers.at(imageHolder->activeImage)->sprite.getPosition().x + (imageHolder->layers.at(imageHolder->activeImage)->texture.getSize().x / 2);
                    mousePos.y = mousePos.y - imageHolder->layers.at(imageHolder->activeImage)->sprite.getPosition().y + (imageHolder->layers.at(imageHolder->activeImage)->texture.getSize().y / 2);
                    
                    imageHolder->layers.at(imageHolder->activeImage)->image.setPixel(mousePos.x, mousePos.y, sf::Color(0, 0, 0));
                    imageHolder->layers.at(imageHolder->activeImage)->image.setPixel(mousePos.x - 1, mousePos.y, sf::Color(0, 0, 0));
                    imageHolder->layers.at(imageHolder->activeImage)->image.setPixel(mousePos.x + 1, mousePos.y, sf::Color(0, 0, 0));
                    imageHolder->layers.at(imageHolder->activeImage)->image.setPixel(mousePos.x, mousePos.y - 1, sf::Color(0, 0, 0));
                    imageHolder->layers.at(imageHolder->activeImage)->image.setPixel(mousePos.x, mousePos.y + 1, sf::Color(0, 0, 0));
                    
                    //Update the sprite's texture with the changes.
                    imageHolder->layers.at(imageHolder->activeImage)->texture.update(imageHolder->layers.at(imageHolder->activeImage)->image);
                }
            }
            
            window.clear();
            
            //Image Drawing
            DrawImages(window, imageHolder);
            
            //Menu Drawing
            DrawMenus(window, imageHolder, buttons);
            
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
