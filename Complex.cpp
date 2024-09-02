//guyes134@gmail.com

#include "Complex.hpp"
#include <cmath>
#include <sstream>

/**
 * @brief Constructs a complex number.
 *
 * @param r The real part of the complex number.
 * @param i The imaginary part of the complex number.
 */
Complex::Complex(double r, double i) : real(r), imag(i) {}

/**
 * @brief Gets the real part of the complex number.
 *
 * @return The real part.
 */
double Complex::getReal() const {
    return real;
}

/**
 * @brief Gets the imaginary part of the complex number.
 *
 * @return The imaginary part.
 */
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

// Overload the stream insertion operator for output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}
