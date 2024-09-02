//guyes134@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

/**
 * @brief A class representing a complex number.
 */
class Complex {
private:
    double real;  ///< The real part of the complex number.
    double imag;  ///< The imaginary part of the complex number.

public:
    Complex(double r = 0.0, double i = 0.0);

    double getReal() const;
    double getImag() const;


    // Overloaded operators
    bool operator<(const Complex& other) const;
    bool operator==(const Complex& other) const;


    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_HPP
