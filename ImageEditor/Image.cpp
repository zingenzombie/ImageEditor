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
    
    if(type == "tga"){
        return new TGA(fileAddress);
    }
    
};

Image::Image(){
    
}

void Image::TGA(string fileAddress){
    
    ifstream file(fileAddress, ios_base::binary);
    
    Header header;
    
    file.read((char *)&header, 18);

    pixels = new vector<vector<Pixel>>(header.height, vector<Pixel>(header.width, Pixel()));

    for(short i = 0; i < header.height; i++){
        for(short j = 0; j < header.width; j++){
            
            /*
            char *b;
            char *g;
            char *r;
                
            file.read((char *)&b, 1);
            file.read((char *)&g, 1);
            file.read((char *)&r, 1);
            */
             
            
            file.read((char *)&pixels->at(i).at(j).b, 1);
            file.read((char *)&pixels->at(i).at(j).g, 1);
            file.read((char *)&pixels->at(i).at(j).r, 1);
             
        }
    }
}
