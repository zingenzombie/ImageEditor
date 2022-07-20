//
//  Image.hpp
//  ImageEditor
//
//  Created by Chase Hap on 7/19/22.
//  Copyright © 2022 Chase Hap. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Image;

Image* ImageImporter(string fileAddress);

class Image{
public:
    struct __attribute__ ((packed)) Pixel;
    
    Image();
    Image(string fileName);
    
    void TGA(string fileName);
    
    vector<vector<Pixel>> *pixels;
    
    struct __attribute__ ((packed)) Pixel{
        char r = 0, g = 0, b = 0;
    };
    
    struct __attribute__ ((packed)) Header{
            char idLength;
            char colorMapType;
            char dataTypeCode;
            short colorMapOrigin;
            short colorMapLength;
            char colorMapDepth;
            short xOrigin;
            short yOrigin;
            short width;
            short height;
            char bitsPerPixel;
            char imageDescriptor;
        };
};

#endif /* Image_hpp */
