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
    
    if(type == "png"){
        return new PNG(fileAddress);
    }
    
    if(type == "tga"){
        return new TGA(fileAddress);
    }
    
};

Image::Image(){
    
}

PNG::PNG(){}

PNG::PNG(string fileAddress){
    
}

TGA::TGA(){}

TGA::TGA(string fileAddress){
    
    ifstream file(fileAddress, ios_base::binary);

    /*
    file.read((char *)&header.idLength, 1);
    file.read((char *)&header.colorMapType, 1);
    file.read((char *)&header.dataTypeCode, 1);
    file.read((char *)&header.colorMapOrigin, 2);
    file.read((char *)&header.colorMapLength, 2);
    file.read((char *)&header.colorMapDepth, 1);
    file.read((char *)&header.xOrigin, 2);
    file.read((char *)&header.yOrigin, 2);
    file.read((char *)&header.width, 2);
    file.read((char *)&header.height, 2);
    file.read((char *)&header.bitsPerPixel, 1);
    file.read((char *)&header.imageDescriptor, 1);
    */
    
    file.read((char *)&header, 18);

    pixels = new vector<vector<Pixel>>(header.height, vector<Pixel>(header.width, Pixel()));

    for(short i = 0; i < header.height; i++){
        for(short j = 0; j < header.width; j++){
                file.read((char *)&pixels->at(i).at(j).b, 1);
                file.read((char *)&pixels->at(i).at(j).g, 1);
                file.read((char *)&pixels->at(i).at(j).r, 1);
        }
    }
}
