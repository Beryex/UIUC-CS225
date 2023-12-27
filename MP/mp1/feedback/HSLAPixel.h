#ifndef HSLAPixel_H
#define HSLAPixel_H

namespace cs225{
    class HSLAPixel {
        public:
            double h;                                   // hue of the pixel with range [0,360]
            double s;                                   // saturation of the pixel with range [0,1]
            double l;                                   // luminance of the pixel with range [0,1]
            double a;                                   // alpha of the pixel with range [0,1]
            HSLAPixel();
            HSLAPixel(double hue, double saturation, double luminance);
            HSLAPixel(double hue, double saturation, double luminance, double alpha);
    };
}

#endif