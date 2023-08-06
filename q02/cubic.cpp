#include <iostream>
#include "cubic.h"

using namespace std;

Cubic::Cubic(){
    // Nothing
}

Cubic::Cubic(float co1, float co2, float co3, float co4){
    poly = Polynomial(3);
    poly.setCoeff(0, co4);
    poly.setCoeff(1, co3);
    poly.setCoeff(2, co2);
    poly.setCoeff(3, co1);
    cout << poly << endl;
}