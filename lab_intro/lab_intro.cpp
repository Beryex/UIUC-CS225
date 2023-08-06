#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace std;
using namespace cs225;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel->s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  // check whether the parameters are valid
  if (centerX < 0 || (unsigned)(centerX) > image.width() || centerY < 0|| (unsigned)(centerY) > image.height()){
    cout << "bad centerX or bad centerY" << endl;
    return image;
  }

  // update each pixel's luminance according to its distance to center
  for (unsigned x = 0; x < image.width(); x++){
    for (unsigned y = 0; y < image.height(); y++){
      HSLAPixel *pixel = image.getPixel(x, y);
      // compute distance
      unsigned distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

      // update luminance
      if (distance > 200){
        pixel->l = 0;
      } else {
        pixel->l = pixel->l * (1 - 0.005 * distance);
      }
    }
  }
  return image;
}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  for (unsigned x = 0; x < image.width(); x++){
    for (unsigned y = 0; y < image.height(); y++){
      HSLAPixel *pixel = image.getPixel(x, y);
      // change color according to distance to orange(11) and blue(216)
      if (pixel->h <= 113 || pixel->h >= 294){      // means closer to orange
        pixel->h = 11.0;
      } else {
        pixel->h = 216.0;
      }
    }
  }
  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  // check whether parameters are valid, if not, resize
  if ((firstImage.width() != secondImage.width()) || (firstImage.height() != secondImage.height())){
    secondImage.resize(firstImage.width(), firstImage.height());
  }

  // update first image's luminance according to second image's luminance
  for (unsigned x = 0; x < secondImage.width(); x++){
    for (unsigned y = 0; y < secondImage.height(); y++){
      HSLAPixel *pixel1 = firstImage.getPixel(x, y);
      HSLAPixel *pixel2 = secondImage.getPixel(x, y);
      if (pixel2->l == 1){
        pixel1->l = pixel1->l + 0.2;
      } 
    }
  }
  return firstImage;
}
