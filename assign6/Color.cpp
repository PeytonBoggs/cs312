#include "Color.hpp"

Color Color::add(const double &c) {
    return Color(R + c, G + c, B + c);
}

Color Color::operator+(const double &c) {
    return Color(R + c, G + c, B + c);
}

Color Color::add(const Color &c) {
    return Color(R + c.R, G + c.G, B + c.B);
}

Color Color::operator+(const Color &c) {
    return Color(R + c.R, G + c.G, B + c.B);
}

Color Color::mult_scalar(const double &c) {
    return Color(R * c, G * c, B * c);
}

Color Color::operator*(const double &c) {
    return mult_scalar(c);
}

void Color::cap() {
    if (this->R > 1) { this->R = 1; };
    if (this->G > 1) { this->G = 1; };
    if (this->B > 1) { this->B = 1; };
}