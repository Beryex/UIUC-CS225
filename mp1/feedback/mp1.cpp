#include <string>
#include <iostream>

#include "mp1.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;
using namespace std;        

// rotate the image in inputfile 180 degrees and output in outputfile
void rotate(string inputFile, string outputFile) {
    // initialize two PNG to deal with
    PNG in_image;
    if(!in_image.readFromFile(inputFile)){
        cout << "bad input file" << endl;
        return;
    }
    PNG out_image(in_image);

    // copy every pixel to corresponding position to achieve the rotation
    for(unsigned x = 0; x < in_image.width(); x++){
        for(unsigned y = 0; y < in_image.height(); y++){
            HSLAPixel* in_pixel = in_image.getPixel(x, y);
            HSLAPixel* out_pixel = out_image.getPixel(in_image.width() - x - 1, in_image.height() - y - 1);
            out_pixel->a = in_pixel->a;
            out_pixel->h = in_pixel->h;
            out_pixel->l = in_pixel->l;
            out_pixel->s = in_pixel->s;
        }
    }

    // output the image into the outputFile
    if(!out_image.writeToFile(outputFile)){
        cout << "can not output into outputFile" << endl;
        return;
    }
    return;
}
