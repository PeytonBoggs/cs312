#ifndef COLOR_H
#define COLOR_H

class Color{
        double R{};
        double G{};
        double B{};
    public:
        Color(double R, double G, double B) : R(R), G(G), B(B) {};
        Color() {};

        double getR() { return R; };
        double getG() { return G; };
        double getB() { return B; };

        Color add(const double &c);
        Color operator+(const double &c);
        Color add(const Color &c);
        Color operator+(const Color &c);

        Color mult_scalar(const double &c);
        Color operator*(const double &c);

        void cap();
};

#endif
