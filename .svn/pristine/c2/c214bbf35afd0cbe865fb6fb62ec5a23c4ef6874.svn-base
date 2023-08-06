#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ImageTraversal::Iterator begin() const;
  ImageTraversal::Iterator end() const;
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool get_visited(Point point);

private:
  double tolerance_;
  queue<Point> Points_;
  PNG png_;
  Point start_;
  vector<bool> visited_;
  bool _check(const Point &point) const;
};

#endif
