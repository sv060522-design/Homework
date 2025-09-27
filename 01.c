#include <stdio.h>
#include <math.h>
struct point
{
    double x;
    double y;
};
typedef struct point Point;
struct triangle
{
    Point a;
    Point b;
    Point c;
};
typedef struct triangle Triangle;
void print_point(Point p)
{
    printf("(%.2f, %.2f)", p.x, p.y);
}
void print_triangle(Triangle* t)
{
    printf("{");
    print_point(t->a);
    printf(", ");
    print_point(t->b);
    printf(", ");
    print_point(t->c);
    printf("}\n");
}
double distance(Point p1, Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}
double get_triangle_perimeter(const Triangle* t)
{
    return distance(t->a, t->b) + distance(t->b, t->c) + distance(t->c, t->a);
}
Triangle moved_triangle(const Triangle* t, Point vector)
{
    Triangle result;
    result.a.x = t->a.x + vector.x;
    result.a.y = t->a.y + vector.y;
    result.b.x = t->b.x + vector.x;
    result.b.y = t->b.y + vector.y;
    result.c.x = t->c.x + vector.x;
    result.c.y = t->c.y + vector.y;
    return result;
}
void move_triangle(Triangle* t, Point vector)
{
    t->a.x += vector.x;
    t->a.y += vector.y;
    t->b.x += vector.x;
    t->b.y += vector.y;
    t->c.x += vector.x;
    t->c.y += vector.y;
}
int main()
{
    Triangle t = {{1.00, 0.00}, {0.50, 2.00}, {0.00, 1.50}};
    printf("Perimeter = %.2f\n", get_triangle_perimeter(&t));
    Point d = {1.0, 1.0};
    print_triangle(&t);
    move_triangle(&t, d);
    print_triangle(&t);
    return 0;
}