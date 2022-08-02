//
//  ImageHolder.hpp
//  ImageEditor
//
//  Created by Chase Hap on 7/30/22.
//  Copyright © 2022 Chase Hap. All rights reserved.
//

#ifndef ImageHolder_hpp
#define ImageHolder_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class ImageHolder{
public:
    class Image{
    public:
        Image(string imageName){
            try{
                image.loadFromFile(imageName);
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                
                sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
            }
            catch(exception){
                cout << "Warning, no image " << imageName << " found." << endl;
            }
        };
        
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
    };
    
    ImageHolder(){}
    
    void AddLayer(string imageName){
        layers.push_back(new Image(imageName));
        
        activeImage++;
    }
    
    vector<Image*> layers;
    
    int activeImage = -1;
};

#endif /* ImageHolder_hpp */
