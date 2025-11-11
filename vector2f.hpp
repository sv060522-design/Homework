#pragma once
#include <iostream>

class Vector2f {
public:
    float x, y;

    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
};

Vector2f operator+(const Vector2f& a, const Vector2f& b) {
    return Vector2f(a.x + b.x, a.y + b.y);
}

Vector2f operator-(const Vector2f& a, const Vector2f& b) {
    return Vector2f(a.x - b.x, a.y - b.y);
}

Vector2f operator*(const Vector2f& a, float b) {
    return Vector2f(a.x * b, a.y * b);
}

Vector2f operator*(float a, const Vector2f& b) {
    return Vector2f(b.x * a, b.y * a);
}

float operator*(const Vector2f& a, const Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

Vector2f operator+(const Vector2f& a) {
    return a;
}

Vector2f operator-(const Vector2f& a) {
    return Vector2f(-a.x, -a.y);
}

bool operator==(const Vector2f& a, const Vector2f& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector2f& a, const Vector2f& b) {
    return !(a == b);
}

Vector2f& operator+=(Vector2f& a, const Vector2f& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2f& operator-=(Vector2f& a, const Vector2f& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Vector2f& operator*=(Vector2f& a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

Vector2f& operator/=(Vector2f& a, float b) {
    a.x /= b;
    a.y /= b;
    return a;
}

std::ostream& operator<<(std::ostream& out, const Vector2f& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Vector2f& v) {
    in >> v.x >> v.y;
    return in;
}