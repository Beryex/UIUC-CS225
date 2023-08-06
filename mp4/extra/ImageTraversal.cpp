#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

Point ImageTraversal::Garbage_ = Point(UINT16_MAX, UINT16_MAX);

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  cur_traversal_ = NULL;
  cur_point_ = Garbage_;
}

/**
 * iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal* cur_traversal) {
  /** @todo [Part 1] */
  cur_traversal_ = cur_traversal;
  cur_point_ = cur_traversal_->peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  cur_traversal_->add(cur_traversal_->pop());
  while(!cur_traversal_->empty() && cur_traversal_->get_visited(cur_traversal_->peek()) == true){
    cur_traversal_->pop();
  }
  cur_point_ = cur_traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return cur_point_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(cur_traversal_ == NULL && other.cur_traversal_ == NULL) return false;
  if(cur_traversal_ == NULL || other.cur_traversal_ == NULL) return true;
  if(cur_point_ == Garbage_ && other.cur_point_ == Garbage_) return false;
  return !(cur_point_ == other.cur_point_);
}

/**
 * helper function to set the cur_point_.
 */
void ImageTraversal::Iterator::set_point(const Point &point) {
  /** @todo [Part 1] */
  cur_point_ = point;
}
