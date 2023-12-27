#include <iostream>

#include "Image.h"

namespace cs225{
    class StickerSheet{
        public:
        StickerSheet();
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index) const;
        Image render() const;

        private:
        Image Garbage_;
        Image Base_;
        unsigned max_;
        Image* Scene_;
        int32_t* start_x_;
        int32_t* start_y_;
    };
}