#ifndef QUAD_H
#define QUAD_H

#include "polynomial.h"

class Cubic: public Polynomial     {

  public:
    // Default constructor
    virtual ~Cubic();

    // four-parameter constructor
    Cubic(float co1, float co2, float co3, float co4);

    private:
    Polynomial poly;

};

#endif


