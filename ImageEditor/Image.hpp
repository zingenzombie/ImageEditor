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
    struct __attribute__ ((packed)) pixel;
    
    Image();
    Image(string filename);
    
    virtual vector<vector<pixel>> *Pixels() const{};
    
    /*struct __attribute__ ((packed)) pixel{
        char r = 0, g = 0, b = 0;
    };*/
};

class PNG : virtual public Image{
public:
    PNG();
    PNG(string fileAddress);
    
    struct __attribute__ ((packed)) Header{
        
    };
};

class TGA : virtual public Image{
public:
    
    struct __attribute__ ((packed)) Pixel;
    
    TGA();
    TGA(string fileAddress);
    
    vector<vector<Pixel>> *Pixels(){return pixels;};
    
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
    
    vector<vector<Pixel>> *pixels;
    
    Header header;
    
    struct __attribute__ ((packed)) Pixel {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
    };
};

#endif /* Image_hpp */
