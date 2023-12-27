#include <iostream>
#include "polynomial.h"
#include "cubic.h"

using namespace std;

int main() {

   cout << "default constructor" << endl;
   Polynomial p1;
   cout << p1 << endl << endl;

   cout << "setCoeff method" << endl;
   p1.setCoeff(1, -1.0);
   p1.setCoeff(0, 0.0);
   cout << p1 << endl << endl;

   cout << "getCoeff method" << endl;
   cout << p1.getCoeff(1) << endl << endl;

   cout << "one-paraeter constructor" << endl;
   Polynomial p2(4);
   cout << p2 << endl << endl;

   cout << "getPolyOrder method" << endl;
   cout << p2.getPolyOrder() << endl << endl;

   cout << "copy constructor" << endl;
   p2.setCoeff(4, -4.0);
   p2.setCoeff(3, -3.0);
   p2.setCoeff(2, -2.0);
   p2.setCoeff(1, -1.0);
   p2.setCoeff(0, 0.0);
   Polynomial p3(p2);
   cout << p3 << endl << endl;

   cout << "assignment operator" << endl;
   Polynomial p4;
   p4 = p3;
   cout << p3 << endl << endl;

   cout << "+ operator" << endl;
   p1.setCoeff(0, -0.5);
   Polynomial p5;
   p5 = p1 + p2;
   cout << p5 << endl << endl;

   cout << "destructor" << endl;
   Polynomial *p6 = new Polynomial;
   delete p6;
   cout << endl;

   cout << "cubic default constructor" << endl;
   Cubic q1;
   cout << q1 << endl << endl;

   cout << "cubic special constructor" << endl;
   Cubic q2(-3, -2, -1, 0);
   cout << q2 << endl;

   return 0;
}

