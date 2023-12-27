#include <iostream>
#include "polynomial.h"

using namespace std;

// Default constructor
// constructs a first-order polynomial with all coefficients set to 1.
Polynomial::Polynomial(){
    order_ = 1;
    a_ = new float[order_ + 1];
    for (unsigned i = 0; i < order_ + 1; i++){
        a_[i] = 1;
    }
}

// One-parameter constructor
// constructs a polynomial of user-supplied order with all coefficients set to 1.
Polynomial::Polynomial(unsigned int order){
    order_ = order;
    a_ = new float[order_ + 1];
    for (unsigned i = 0; i < order + 1; i++){
        a_[i] = 1;
    }
}

// helper function to copy - IMPLEMENT ME
void Polynomial::copy_(const Polynomial &p) {
    order_ = p.getPolyOrder();
    for (unsigned i = 0; i < order_ + 1; i++){
        a_[i] = p.getCoeff(i);
    }
}

// helper function to destroy - IMPLEMENT ME
void Polynomial::destroy_() {
    delete[] a_;
}

// Copy constructor - must use copy_() function
// constructs a new polynomial that is a copy of an existing polynomial
Polynomial::Polynomial(const Polynomial& other){
    a_ = new float[other.getPolyOrder() + 1];
    copy_(other);
}

// Destructor - must use destroy_() function
// destroys a polynomial object
Polynomial::~Polynomial(){
    destroy_();
}

// Assignment operator - must use copy_() function
// assigns rhs Polynomial object to 'this' Polynomial object
Polynomial& Polynomial::operator=(const Polynomial& other){
    copy_(other);
    return *this;
}

// getPolyOrder
// returns the polynomial order
unsigned int Polynomial::getPolyOrder() const{
    return order_;
}

// getCoeff
// returns the coefficient of the x^i term in polynomial
// note: If the object does not contain a term with power i (e.g., 
//       i>order_), a coefficient value of zero is returned.
float Polynomial::getCoeff(unsigned int i) const{
    if (i > order_){
        return 0;
    }
    return a_[i];
}

// setCoeff
// If i <= order_, set a term, value*x^i, in a polynomial
void Polynomial::setCoeff(unsigned int i, float coeff){
    if(i <= order_){
        a_[i] = coeff;
    }
}

// addition operator
// adds two polynomials together and returns a new polynomial
Polynomial Polynomial::operator+(const Polynomial& other){
    Polynomial A;
    if (order_ < other.getPolyOrder()){
        unsigned int order1 = order_;
        Polynomial poly(other.getPolyOrder());
        poly.order_ = other.getPolyOrder();
        for (unsigned int i = 0; i <= order1; i++){
            poly.a_[i] = a_[i] + other.a_[i];
        }
        for (unsigned int i = order1 + 1; i <= other.getPolyOrder() + 1; i++){
            poly.a_[i] = other.a_[i];
        }
        return poly;
    } else if (order_ > other.getPolyOrder()){
        unsigned int order1 = other.getPolyOrder();
        Polynomial poly(order_);
        poly.order_ = order_;
        for (unsigned int i = 0; i <= order1; i++){
            poly.a_[i] = a_[i] + other.a_[i];
        }
        for (unsigned int i = other.getPolyOrder() + 1; i <= order_ + 1; i++){
            poly.a_[i] = a_[i];
        }
        return poly;
    } else {
        unsigned int order1 = other.getPolyOrder();
        Polynomial poly(other.getPolyOrder());
        poly.order_ = order_;
        for (unsigned int i = 0; i <= order1; i++){
            poly.a_[i] = a_[i] + other.a_[i];
        }
        return poly;
    }
}


// insertion operator for output
// note: This function has been provided for you -- DO NOT CHANGE IT!
ostream & operator << (ostream &out, const Polynomial& p)
{
    bool printed = false;

    for (int i = p.order_; i >= 0; i--)
    {
        float c = p.a_[i];

        if (c != 0.0)
        {
            if (printed) out << " + ";
            printed = true;
            out << c << "*X^" << i;
        }
    }

    return out;
}
