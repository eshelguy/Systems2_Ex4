//guyes134@gmail.com

#include "Complex.hpp"
#include <cmath>
#include <sstream>

// Constructor
Complex::Complex(double r, double i) : real(r), imag(i) {}

// Accessor methods
double Complex::getReal() const {
    return real;
}

double Complex::getImag() const {
    return imag;
}

// Overload the comparison operators
bool Complex::operator<(const Complex& other) const {
    return std::sqrt(real * real + imag * imag) < std::sqrt(other.real * real + other.imag * imag);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

// Convert to string for display
std::string Complex::toString() const {
    std::ostringstream oss;
    oss << "(" << real << " + " << imag << "i)";
    return oss.str();
}

// Overload the stream insertion operator for output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}
