#include "StickerSheet.h"

namespace cs225{
    // Initializes the StickerSheet with a base picture and the ability to hold a max number of stickers
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        max_ = max;
        Base_ = picture;
        Garbage_ = Image();
        Scene_ = new Image[max];
        start_x_ = new int32_t[max_];
        start_y_ = new int32_t[max_];
        // initialization
        for (unsigned i = 0; i < max_; i++){
            Scene_[i] = Garbage_;
            start_x_[i] = -1;
            start_y_[i] = -1;
        }
    }

    // Frees all space that was dynamically allocated by this StickerSheet
    StickerSheet::~StickerSheet(){
        delete[] Scene_; Scene_ = NULL;
        delete[] start_x_; start_x_ = NULL;
        delete[] start_y_; start_y_ = NULL;
    }

    // Make this StickerSheet an independent copy of the source
    StickerSheet::StickerSheet(const StickerSheet &other){
        max_ = other.max_;
        Base_ = other.Base_;
        Garbage_ = other.Garbage_;
        Scene_ = new Image[max_];
        start_x_ = new int32_t[max_];
        start_y_ = new int32_t[max_];
        for (unsigned i = 0; i < max_; i++){
            Scene_[i] = other.Scene_[i];
            start_x_[i] = other.start_x_[i];
            start_y_[i] = other.start_y_[i];
        }
    }

    // The assignment operator for the StickerSheet class
    const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
        max_ = other.max_;
        Base_ = other.Base_;
        Garbage_ = other.Garbage_;
        for (unsigned i = 0; i < max_; i++){
            Scene_[i] = other.Scene_[i];
            start_x_[i] = other.start_x_[i];
            start_y_[i] = other.start_y_[i];
        }
        return *this;
    }

    // Modifies the maximum number of stickers that can be stored on this StickerSheet
    void StickerSheet::changeMaxStickers(unsigned max){
        max_ = max;
        // build a new Scene_ and delete the old one 
        Image* Original_pt = Scene_;
        int32_t* Original_x = start_x_;
        int32_t* Original_y = start_y_;
        Scene_ = new Image[max_];
        Original_x = new int32_t[max_];
        Original_y = new int32_t[max_];
        // initialization
        for (unsigned i = 0; i < max_; i++){
            Scene_[i] = Garbage_;
            start_x_[i] = -1;
            start_y_[i] = -1;
        }
        for (unsigned i = 0; i < max_; i++){
            Scene_[i] = Original_pt[i];
            start_x_[i] = Original_x[i];
            start_y_[i] = Original_y[i];
        }
        delete[] Original_pt; Original_pt = NULL;
        delete[] Original_x; Original_x = NULL;
        delete[] Original_y; Original_y = NULL;
    }

    // Add a sticker to the StickerSheet, the top-left of the sticker's Image is at (x, y) on the StickerSheet
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        for(unsigned i = 0; i < max_; i++){
            if(Scene_[i] == Garbage_){
                Scene_[i] = sticker;
                start_x_[i] = x;
                start_y_[i] = y;
                return i;
            }
        }
        return -1;
    }

    // Changes the x and y coordinates of the Image in the specified layer
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
        if (index >= max_ || Scene_[index] == Garbage_){
            cout << "bad input parameter" << endl;
            return false;
        }
        start_x_[index] = x;
        start_y_[index] = y;
        return true;
    }

    // Removes the sticker at the given zero-based layer index
    void StickerSheet::removeSticker(unsigned index){
        if(index >= max_){
            cout << "bad input parameter: index" << endl;
            return;
        }
        Scene_[index] = Garbage_;
        start_x_[index] = -1;
        start_y_[index] = -1;
    }

    // Returns a pointer to the sticker at the specified index
    Image* StickerSheet::getSticker(unsigned index) const{
        if (Scene_[index] == Garbage_ || index >= max_){
            cout << "bad input parameter: index" << endl;
            return NULL;
        }
        return &Scene_[index];
    }

    // Renders the whole StickerSheet on one Image and returns that Image
    Image StickerSheet::render() const{
        Image output(Base_);
        for(unsigned i = 0; i < max_; i++){
            if(Scene_[i] == Garbage_){
                continue;
            }
            for(unsigned Tar_x = 0; Tar_x < Scene_[i].width(); Tar_x++){
                for(unsigned Tar_y = 0; Tar_y < Scene_[i].height(); Tar_y++){
                    if (output.width() - 1 < Tar_x + start_x_[i]){
                        output.resize(Tar_x + start_x_[i] + 1, output.height());
                    }
                    if (output.height() - 1 < Tar_y + start_y_[i]){
                        output.resize(output.width(), Tar_y + start_y_[i] + 1);
                    }
                    HSLAPixel* Base_Pixel = output.getPixel(Tar_x + start_x_[i], Tar_y + start_y_[i]);
                    HSLAPixel* Tar_Pixel = Scene_[i].getPixel(Tar_x, Tar_y);
                    if (Tar_Pixel->a != 0){
                        Base_Pixel->a = Tar_Pixel->a;
                        Base_Pixel->h = Tar_Pixel->h;
                        Base_Pixel->l = Tar_Pixel->l;
                        Base_Pixel->s = Tar_Pixel->s;
                    }
                }
            }
        }
        return output;
    }
}