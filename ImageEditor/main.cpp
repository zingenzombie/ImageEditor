#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Image.hpp"

using namespace std;

int main(int argc, char const** argv)
{
    
    Image *tmp = ImageImporter("EXAMPLE_extracredit.tga");
    
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Image Editor");
    
    window.setVerticalSyncEnabled(true);
    
    while(true){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            
            window.clear();
            
            window.display();
        }
    }
    
    return EXIT_SUCCESS;
}
