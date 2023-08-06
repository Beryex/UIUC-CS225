#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;
using namespace std;

/**
 * A base class for traversal algorithms on images.
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(ImageTraversal* cur_traversal);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
    void set_point(const Point &point);
  
  private:
    ImageTraversal* cur_traversal_;
    Point cur_point_;
  };  

public:
  virtual Iterator begin() = 0;
  virtual Iterator end() const = 0;

  virtual void add(const Point & t) = 0;
  virtual Point pop() = 0;
  virtual Point peek() const = 0;
  virtual bool empty() const = 0;
  virtual bool get_visited(Point point) = 0;

protected:
  static Point Garbage_;
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);
};




#endif
