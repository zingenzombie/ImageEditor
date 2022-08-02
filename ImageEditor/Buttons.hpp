//
//  Buttons.hpp
//  ImageEditor
//
//  Created by Chase Hap on 7/31/22.
//  Copyright © 2022 Chase Hap. All rights reserved.
//

#ifndef Buttons_hpp
#define Buttons_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>

using namespace std;

class Buttons{
public:
    class Button{
    public:
        Button(){
            rectangle.setSize(sf::Vector2f(25, 25));
            rectangle.setPosition(25, 25);
        }
        Button(sf::Vector2f dimensions, sf::Vector2i position, sf::Color color, string words, void (*function)()){
            this->function = function;
            this->words = words;
            rectangle.setSize(dimensions);
            rectangle.setOrigin(dimensions.x / 2, dimensions.y / 2);
            rectangle.setPosition(position.x, position.y);
            rectangle.setFillColor(color);
        }
        
        bool HasBeenClicked(sf::Vector2i &mousePos){
            if(rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                return true;
            }
        }
        
        sf::RectangleShape rectangle;
        
        string words;
        
        void (*function)();
    };
    Buttons(){}
    
    void AddButton(){
        buttons.push_back(new Button());
    }
    
    void AddButton(sf::Vector2f dimensions, sf::Vector2i position, sf::Color color, string words, void (*function)()){
        buttons.push_back(new Button(dimensions, position, color, words, function));
    }
    
    vector<Button*> buttons;
};

#endif /* Buttons_hpp */
