#include "StickerSheet.h"

using namespace cs225;

int main() {
  Image MY_base;
  Image Sticker_1;
  Image Sticker_2;
  Image Sticker_3;
  MY_base.readFromFile("MY_base.png");
  Sticker_1.readFromFile("Sticker1.png");
  Sticker_2.readFromFile("Sticker2.png");
  Sticker_3.readFromFile("Sticker3.png");
  StickerSheet A(MY_base, 2);
  StickerSheet B = A;
  StickerSheet MY(B);
  MY.changeMaxStickers(3);
  MY.addSticker(Sticker_1, 10, 20);
  MY.addSticker(Sticker_2, 200, 200);
  MY.addSticker(Sticker_3, 10, 400);
  MY.translate(2, 200, 400);
  MY.removeSticker(1);
  MY.addSticker(Sticker_1, 200, 200);
  Image output;
  output = MY.render();
  output.writeToFile("myImage.png");
  return 0;
}
