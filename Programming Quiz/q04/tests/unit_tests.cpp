#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Image.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

#include "../StickerSheet.h"

TEST_CASE("scale", "[weight=20][part=2]") {

  Image alma;
  alma.readFromFile("alma.png");

  Image sticker[5];
  sticker[0].readFromFile("tests/i.png");
  sticker[1].readFromFile("tests/zju.png");
  sticker[2].readFromFile("tests/i.png");
  sticker[3].readFromFile("tests/zju.png");
  sticker[4].readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);

  for (int i = 0; i < 5; i++) {
    sheet.addSticker(sticker[i], 38*i*i, 12*i*i, (i+1)/4.0);
  }

  Image rendered = sheet.render();
  rendered.writeToFile("tests/actual_scale.png");

  Image expected;
  expected.readFromFile("tests/expected_scale.png");

  REQUIRE( rendered == expected );
}

TEST_CASE("rotate_0", "[weight=5][part=1]") {

  Image alma;
  alma.readFromFile("alma.png");

  alma.rotate(0);
  alma.writeToFile("tests/actual_alma0.png");

  Image expected;
  expected.readFromFile("tests/alma0.png");

  REQUIRE( alma == expected );
}

TEST_CASE("rotate_90", "[weight=5][part=1]") {

  Image alma;
  alma.readFromFile("alma.png");

  alma.rotate(90);
  alma.writeToFile("tests/actual_alma90.png");

  Image expected;
  expected.readFromFile("tests/alma90.png");

  REQUIRE( alma == expected );
}

TEST_CASE("rotate_180", "[weight=5][part=1]") {

  Image alma;
  alma.readFromFile("alma.png");

  alma.rotate(180);
  alma.writeToFile("tests/actual_alma180.png");

  Image expected;
  expected.readFromFile("tests/alma180.png");

  REQUIRE( alma == expected );
}

TEST_CASE("rotate_270", "[weight=5][part=1]") {

  Image alma;
  alma.readFromFile("alma.png");

  alma.rotate(270);
  alma.writeToFile("tests/actual_alma270.png");

  Image expected;
  expected.readFromFile("tests/alma270.png");

  REQUIRE( alma == expected );
}


