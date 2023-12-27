#include "HSLAPixel.h"

namespace cs225{
    // constucts a default HSLAPixel
    HSLAPixel::HSLAPixel()
    {
        h = 0.0;
        s = 1.0;
        l = 1.0;
        a = 1.0;
    }

    // constructs an opaque HSLAPixel with the given hue, saturetion, and luminance values
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) 
    {
        h = hue;
        s = saturation;
        l = luminance;
        a = 1.0;
    }

    // constructs an opaque HSLAPixel with the given hue, saturation, luminance, and alpha values
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) 
    {
        h = hue;
        s = saturation;
        l = luminance;
        a = alpha;
    }
}