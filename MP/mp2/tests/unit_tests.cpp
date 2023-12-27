#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Image.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

Image createRainbowImage() {
  Image png;
  png.resize(360, 100);

  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel * pixel = png.getPixel(x, y);
      pixel->h = x;
      pixel->s = y / 100.0;
      pixel->l = y / 100.0;
    }
  }
  return png;
}


//
// lighten, darken
//
TEST_CASE("Image lighten() works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.lighten();

  REQUIRE( img.getPixel(10, 10)->l + 0.1 == result.getPixel(10, 10)->l );
  REQUIRE( 1.0 == result.getPixel(10, 95)->l );
}

TEST_CASE("Image darken(0.2) works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.darken(0.2);

  REQUIRE( img.getPixel(50, 50)->l - 0.2 == result.getPixel(50, 50)->l );
  REQUIRE( 0 == result.getPixel(5, 5)->l );
}


//
// saturate, desaturate
//
TEST_CASE("Image {de}saturate() works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.saturate();

  REQUIRE( img.getPixel(10, 10)->s + 0.1 == result.getPixel(10, 10)->s );
  
  result.desaturate();
  
  REQUIRE( img.getPixel(10, 10)->s == result.getPixel(10, 10)->s );
}

//
// rotateColor
//
TEST_CASE("Image rotateColor() works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.rotateColor(90);

  REQUIRE( img.getPixel(90, 90)->h + 90 == result.getPixel(90, 90)->h );
  REQUIRE( result.getPixel(340, 90)->h == 70 );
  
  result.rotateColor(-270);
  REQUIRE( result.getPixel(10, 90)->h == 190 );
  
  result.rotateColor(720*10);
  REQUIRE( result.getPixel(10, 90)->h == 190 );
}


//
// scale
//
TEST_CASE("Image scale(2.0) works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(2.0);

  REQUIRE( img.height() * 2 == result.height() );
  REQUIRE( result.getPixel(100, 100)->h > 40 );
  REQUIRE( result.getPixel(100, 100)->h < 60 );
}

TEST_CASE("Image scale(0.5) works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(0.5);

  REQUIRE( img.height() * 0.5 == result.height() );
  
  REQUIRE( result.getPixel(100, 20)->h > 180 );
  REQUIRE( result.getPixel(100, 20)->h < 220 );
}

TEST_CASE("Image scale(1080,200) works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(1080,200);

  REQUIRE( result.width() == 720);
  REQUIRE( result.getPixel(400, 80)->h > 180 );
  REQUIRE( result.getPixel(400, 80)->h < 220 );
}

TEST_CASE("Image scale(180,512) works correctly", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(180,512);
  
  REQUIRE( result.getPixel(100, 20)->h > 180 );
  REQUIRE( result.getPixel(100, 20)->h < 220 );
}

// Part 2 Testing:
#include "../StickerSheet.h"

TEST_CASE("A basic StickerSheet works", "[weight=4][id=provided]") {
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  Image expected;
  expected.readFromFile("tests/expected.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("copy test for StickerSheet", "[weight=2][id=copy]") {
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  StickerSheet sheet4 = sheet;
  sheet.addSticker(i, 20, 200);
  StickerSheet sheet2(sheet);
  StickerSheet sheet3 = sheet2;

  Image expected;
  expected.readFromFile("tests/expected.png");

  REQUIRE( sheet2.render() == expected );
  REQUIRE( sheet3.render() == expected );
}

TEST_CASE("Several Stickers are out of image", "[weight=2][id=range]") {
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 20, 400);
  sheet.addSticker(i, 800, 400);
  sheet.addSticker(i, 800, 200);

  Image res = sheet.render();
  REQUIRE( res.width() >= 1026 );
  REQUIRE( res.width() < 1280 );
  REQUIRE( res.height() >= 727 );
  REQUIRE( res.height() < 960 );

  REQUIRE( res.getPixel(830,443)->h > 210 );
  REQUIRE( res.getPixel(830,443)->h < 220 );
  REQUIRE( res.getPixel(136,443)->h > 8 );
  REQUIRE( res.getPixel(136,443)->h < 15 );
}

TEST_CASE("Add, remove and change stickers", "[weight=3][id=add]") {
  Image alma;
  alma.readFromFile("tests/alma.png");
  
  Image i;
  i.readFromFile("tests/i.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 20, 400);
  sheet.addSticker(i, 800, 400);
  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 500, 300);
  
  REQUIRE(sheet.addSticker(i,524,211) == -1);
  sheet.removeSticker(3);
  sheet.changeMaxStickers(7);
  REQUIRE( sheet.getSticker(3) == NULL );
  REQUIRE( sheet.translate(3,1,1) == false );
  REQUIRE( sheet.addSticker(i,524,211) == 3 );
  REQUIRE( sheet.translate(3,1,1) == true );
  REQUIRE( sheet.translate(10,1,1) == false );

  StickerSheet* sheet_p = new StickerSheet(i, 3);
  StickerSheet* sheet2_p = new StickerSheet(alma, 3);
  *sheet2_p = *sheet_p;
  delete sheet_p;
  delete sheet2_p;
  
  sheet_p = new StickerSheet(alma, 3);
  REQUIRE( sheet_p->addSticker(i,524,211) == 0 );
  REQUIRE( sheet_p->addSticker(i,524,211) == 1 );
  REQUIRE( sheet_p->addSticker(i,524,211) == 2 );
  sheet_p->changeMaxStickers(1);
  REQUIRE( sheet_p->translate(1,1,1) == false );
  sheet_p->render();
  delete sheet_p;
  
  sheet_p = new StickerSheet(alma, 3);
  sheet_p->changeMaxStickers(0);
  sheet_p->changeMaxStickers(2);
  REQUIRE( sheet_p->addSticker(i,524,211) == 0 );
  REQUIRE( sheet_p->addSticker(i,524,211) == 1 );
  sheet_p->removeSticker(0);
  REQUIRE( sheet_p->addSticker(i,524,211) == 0 );
  REQUIRE( sheet_p->addSticker(i,524,211) == -1 );
  delete sheet_p;
  
  sheet_p = new StickerSheet(alma, 0);
  sheet_p->changeMaxStickers(2);
  REQUIRE( sheet_p->addSticker(i,524,211) == 0 );
  REQUIRE( sheet_p->addSticker(i,524,211) == 1 );
  sheet_p->changeMaxStickers(4);
  REQUIRE( sheet_p->addSticker(i,524,211) == 2 );
  sheet_p->changeMaxStickers(8);
  sheet_p->changeMaxStickers(4);
  delete sheet_p;
  
}