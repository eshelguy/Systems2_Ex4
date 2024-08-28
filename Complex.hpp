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
    /**
     * @brief Constructs a complex number.
     *
     * @param r The real part of the complex number.
     * @param i The imaginary part of the complex number.
     */
    Complex(double r = 0.0, double i = 0.0);

    /**
     * @brief Gets the real part of the complex number.
     *
     * @return The real part.
     */
    double getReal() const;

    /**
     * @brief Gets the imaginary part of the complex number.
     *
     * @return The imaginary part.
     */
    double getImag() const;

    /**
     * @brief Converts the complex number to a string for display.
     *
     * @return A string representation of the complex number.
     */
    std::string toString() const;

    // Overloaded operators
    bool operator<(const Complex& other) const;
    bool operator==(const Complex& other) const;

    /**
     * @brief Overloads the stream insertion operator for output.
     *
     * @param os The output stream.
     * @param c The complex number to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_HPP
