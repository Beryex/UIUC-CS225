#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  // initialize parameters
  png_ = png;
  Points_.push(start);
  start_ = Points_.top();
  tolerance_ = tolerance;
  visited_.resize(png.width() * png.height(), false);
  visited_[start_.y * png_.width() + start_.x] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() const{
  /** @todo [Part 1] */
  ImageTraversal* cur_traversal = (ImageTraversal*)this;
  ImageTraversal::Iterator i(cur_traversal);
  i.set_point(start_);
  return i;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() const{
  /** @todo [Part 1] */
  ImageTraversal* imagetraversal = (ImageTraversal*)this;
  ImageTraversal::Iterator i(imagetraversal);
  i.set_point(Garbage_);
  return i;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  // compute coordinate
  unsigned cur_x = point.x;
  unsigned cur_y = point.y;
  Point right_point(cur_x + 1, cur_y);
  Point below_point(cur_x, cur_y + 1);
  Point left_point(cur_x - 1, cur_y);
  Point above_point(cur_x, cur_y - 1);

  // check all points and push it onto stack if necessary
  if(_check(right_point)){
    Points_.push(right_point);
  }
  if(_check(below_point)){
    Points_.push(below_point);
  }
  if(_check(left_point)){
    Points_.push(left_point);
  }
  if(_check(above_point)){
    Points_.push(above_point);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if(empty()) return Garbage_;
  Point result = Points_.top();
  visited_[result.y*png_.width() + result.x] = true;
  Points_.pop();
  return result;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(empty()) return Garbage_;
  return Points_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return Points_.empty();
}

/**
 * helper function that can check if a point should be pushed in to stack.
 */
bool DFS::_check(const Point &point) const{
  bool result = point.x < png_.width() && point.y < png_.height()
              && visited_[point.y * png_.width() + point.x] == false
              && calculateDelta(*png_.getPixel(point.x, point.y), 
                                *png_.getPixel(start_.x, start_.y)) <= tolerance_;
  return result;
}

bool DFS::get_visited(Point point){
  return visited_[point.y * png_.width() + point.x];
}