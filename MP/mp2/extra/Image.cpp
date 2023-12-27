#include <math.h>

#include "Image.h"

namespace cs225{
    // lighten an Image by increasing the luminance of every pixel by 0.1
    void Image::lighten(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->l += 0.1;
                if (Cur_Pixel->l > 1){
                    Cur_Pixel->l = 1;
                }
            }
        }
    }

    // lighten an Image by increasing the luminance of every pixel by amount
    void Image::lighten(double amount){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->l += amount;
                if (Cur_Pixel->l > 1){
                    Cur_Pixel->l = 1;
                }
            }
        }
    }

    // Darken an Image by decreasing the luminance of every pixel by 0.1
    void Image::darken(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->l -= 0.1;
                if (Cur_Pixel->l < 0){
                    Cur_Pixel->l = 0;
                }
            }
        }
    }

    // darken an Image by decreasing the luminance of every pixel by amount
    void Image::darken(double amount){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->l -= amount;
                if (Cur_Pixel->l < 0){
                    Cur_Pixel->l = 0;
                }
            }
        }
    }

    // Saturates an Image by increasing the saturation of every pixel by 0.1
    void Image::saturate(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->s += 0.1;
                if (Cur_Pixel->s > 1){
                    Cur_Pixel->s = 1;
                }
            }
        }
    }

    // Saturates an Image by increasing the saturation of every pixel by amount
    void Image::saturate(double amount){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->s += amount;
                if (Cur_Pixel->s > 1){
                    Cur_Pixel->s = 1;
                }
            }
        }
    }

    // Desaturates an Image by decreasing the saturation of every pixel by 0.1
    void Image::desaturate(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->s -= 0.1;
                if (Cur_Pixel->s < 0){
                    Cur_Pixel->s = 0;
                }
            }
        }
    }

    // Desaturates an Image by decreasing the saturation of every pixel by amount
    void Image::desaturate(double amount){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->s -= amount;
                if (Cur_Pixel->s < 0){
                    Cur_Pixel->s = 0;
                }
            }
        }
    }

    // Turns the image grayscale
    void Image::grayscale(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->s = 0;
            }
        }
    }

    // Rotates the color wheel by degrees
    void Image::rotateColor(double degrees){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                Cur_Pixel->h += degrees;
                if (Cur_Pixel->h > 360){
                    while (Cur_Pixel->h > 360){
                        Cur_Pixel->h -= 360;
                    }
                } else if (Cur_Pixel->h < 0){
                    while (Cur_Pixel->h < 0){
                        Cur_Pixel->h += 360;
                    }
                }
            }
        }
    }

    // Illinify the image
    void Image::illinify(){
        for(unsigned x = 0; x < this->width(); x++){
            for(unsigned y = 0; y < this->height(); y++){
                HSLAPixel* Cur_Pixel = getPixel(x, y);
                if (Cur_Pixel->h <= 113 || Cur_Pixel->h >= 294){
                    Cur_Pixel->h = 11.0;
                } else {
                    Cur_Pixel->h = 216.0;
                }
            }
        }
    }

    // Scale the Image by a given factor
    void Image::scale(double factor){
        unsigned tar_width = (unsigned)(this->width() * factor);
        unsigned tar_height = (unsigned)(this->height() * factor);
        if (factor < 1){
            unsigned de_width = this->width() - tar_width;
            unsigned de_height = this->height() - tar_height;
            double width_interval = (tar_width / de_width);
            double height_interval = (tar_height / de_height);
            for(unsigned i = 0; i < de_width; i++){
                unsigned de_index = (unsigned)(round((double)(i * width_interval)));
                for(unsigned j = de_index; j < this->width() - 1; j++){
                    for(unsigned m = 0; m < this->height(); m++){
                        HSLAPixel* de_Pixel = getPixel(j, m);
                        HSLAPixel* Tar_Pixel = getPixel(j + 1, m);
                        de_Pixel->a = Tar_Pixel->a;
                        de_Pixel->h = Tar_Pixel->h;
                        de_Pixel->l = Tar_Pixel->l;
                        de_Pixel->s = Tar_Pixel->s;
                    }
                }
            }
            for(unsigned i = 0; i < de_height; i++){
                unsigned de_index = (unsigned)(round((double)(i * height_interval)));
                for(unsigned j = de_index; j < this->height() - 1; j++){
                    for(unsigned m = 0; m < this->width(); m++){
                        HSLAPixel* de_Pixel = getPixel(m, j);
                        HSLAPixel* Tar_Pixel = getPixel(m, j + 1);
                        de_Pixel->a = Tar_Pixel->a;
                        de_Pixel->h = Tar_Pixel->h;
                        de_Pixel->l = Tar_Pixel->l;
                        de_Pixel->s = Tar_Pixel->s;
                    }
                }
            }
            this->resize( tar_width, tar_height);
        } else if (factor > 1){
            unsigned in_width = tar_width - this->width();
            unsigned in_height = tar_height - this->height();
            double width_interval = (tar_width / in_width);
            double height_interval = (tar_height / in_height);
            this->resize( tar_width, tar_height);
            for(unsigned i = 0; i < in_width; i++){
                unsigned in_index = (unsigned)(round((double)(i * width_interval)));
                for(unsigned j = this->width() - 1; j > in_index; j--){
                    for(unsigned m = 0; m < this->height(); m++){
                        HSLAPixel* in_Pixel = getPixel(j - 1, m);
                        HSLAPixel* Tar_Pixel = getPixel(j, m);
                        Tar_Pixel->a = in_Pixel->a;
                        Tar_Pixel->h = in_Pixel->h;
                        Tar_Pixel->l = in_Pixel->l;
                        Tar_Pixel->s = in_Pixel->s;
                    }
                }
            }
            for(unsigned i = 0; i < in_height; i++){
                unsigned in_index = (unsigned)(round((double)(i * height_interval)));
                for(unsigned j = this->height() - 1; j > in_index; j--){
                    for(unsigned m = 0; m < this->width(); m++){
                        HSLAPixel* in_Pixel = getPixel(m, j - 1);
                        HSLAPixel* Tar_Pixel = getPixel(m, j);
                        Tar_Pixel->a = in_Pixel->a;
                        Tar_Pixel->h = in_Pixel->h;
                        Tar_Pixel->l = in_Pixel->l;
                        Tar_Pixel->s = in_Pixel->s;
                    }
                }
            }
        }
    }

    // Scales the image to fit within the size (w * h)
    void Image::scale( unsigned w, unsigned h){
        double factor1 = (double)w / this->width();
        double factor2 = (double)h / this->height();
        if (factor1 > factor2){
            this->scale(factor2);
        } else {
            this->scale(factor1);
        }
    }
}