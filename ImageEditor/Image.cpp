//
//  Image.cpp
//  ImageEditor
//
//  Created by Chase Hap on 7/19/22.
//  Copyright © 2022 Chase Hap. All rights reserved.
//

#include "Image.hpp"

using namespace std;

Image* ImageImporter(string fileAddress){
    
    string type;
    
    int endpoint;
    
    for(int i = fileAddress.size() - 1; i >= 0; i--){
        if(fileAddress.at(i) == '.'){
            endpoint = i;
            break;
        }
    }
    
    for(int i = endpoint + 1; i < fileAddress.size(); i++){
        type += fileAddress.at(i);
    }
    
    Image *image;
    
    if(type == "tga"){
        image = new Image();
        image->TGA(fileAddress);
    }
    return image;
};

Image::Image(){}

void Image::TGA(string fileAddress){
    
    ifstream file(fileAddress, ios_base::binary);
    
    file.read((char *)&header, 18);
    
    /*
    pixelsArr = new unsigned char[((int) header.height * header.width * 3)];
    
    int pos = 0;
    for(int i = 0; i < header.height * header.width; i++){
        file.read((char *)&pixelsArr[pos], 1);
        pos++;
    }
     */

    
    
    pixels = new vector<vector<Pixel>>(header.height, vector<Pixel>(header.width, Pixel()));

    for(short i = 0; i < header.height; i++){
        for(short j = 0; j < header.width; j++){
            file.read((char *)&pixels->at(i).at(j).b, 1);
            file.read((char *)&pixels->at(i).at(j).g, 1);
            file.read((char *)&pixels->at(i).at(j).r, 1);
        }
    }
    
}
