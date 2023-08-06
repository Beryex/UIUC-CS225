#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  ImageTraversal::Iterator begin() const;
  ImageTraversal::Iterator end() const;

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool get_visited(Point point);

private:
  double tolerance_;
  stack<Point> Points_;
  PNG png_;
  Point start_;
  vector<bool> visited_;
  bool _check(const Point &point) const;
};

#endif
