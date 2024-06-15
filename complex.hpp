// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#ifndef COMPLEX_H
#define COMPLEX_H

#endif // COMPLEX_H

#pragma once
#include <iomanip>
#include <sstream>
#include <string>

class Complex {
public:
    double real, imaginary;

    Complex(double r, double i) : real(r), imaginary(i) {}

    inline std::string to_string() const {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << real;
        std::string s_r = stream.str();
        stream.str(std::string());
        stream << std::fixed << std::setprecision(2) << imaginary;
        std::string s_i = stream.str();

        return "(" + s_r + ", " + s_i + ")";
    }
    inline bool operator<(const Complex &other) const { return (real == other.real) ? (imaginary < other.imaginary) : (real < other.real); }

    inline operator std::string() const { return to_string(); }
    inline friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
        os << c.to_string();
        return os;
    }
};
