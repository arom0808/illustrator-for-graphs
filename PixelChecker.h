#pragma once

#include <QObject>
#include <QPointF>
#include <cmath>
#include <tuple>

using std::min;
using std::max;
using std::tie;
using std::make_tuple;

class PixelChecker
{
public:
    PixelChecker();
    bool check(qreal x, qreal y) const;
private:
    struct Circle {
        qreal x0, y0, r;
    public:
        Circle(qreal x0, qreal y0, qreal r) : x0(x0), y0(y0), r(r) {}
        inline bool in(qreal x, qreal y) const { return square_dist_from_center(x, y) <= r * r; }
        inline bool out(qreal x, qreal y) const { return square_dist_from_center(x, y) >= r * r; }
        inline qreal square_dist_from_center(qreal x, qreal y) const { return (x - x0) * (x - x0) + (y - y0) * (y - y0); }
    };
    struct Parabola {
        qreal a, b, c;
    public:
        Parabola(qreal a, qreal b, qreal c) : a(a), b(b), c(c) {}
        Parabola(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
        QPointF point() const;
        inline bool vert_over(qreal x, qreal y) const { return y >= value(x); }
        inline bool vert_under(qreal x, qreal y) const { return y <= value(x); }
        inline bool hor_right(qreal x, qreal y) const { return x >= value(y); }
        inline bool hor_left(qreal x, qreal y) const { return x <= value(y); }
        inline qreal value(qreal x) const { return a * x * x + b * x + c; }
    };
    struct VerticalLine {
        qreal x0;
    public:
        VerticalLine(qreal x0) : x0(x0) {}
        inline bool left(qreal x, qreal y) const { return x <= x0; }
        inline bool right(qreal x, qreal y) const { return x >= x0; }
    };
    struct Line {
        qreal k, b;
    public:
        Line(qreal k, qreal b) : k(k), b(b) {}
        Line(qreal x1, qreal y1, qreal x2, qreal y2);
        inline bool over(qreal x, qreal y) const { return y >= k * x + b; }
        inline bool under(qreal x, qreal y) const { return y <= k * x + b; }
    };
    struct AxesParallelRect{
        qreal x1, y1, x2, y2;
    public:
        AxesParallelRect(qreal x1, qreal y1, qreal x2, qreal y2) : x1(min(x1, x2)), y1(min(y1, y2)), x2(max(x1, x2)), y2(max(y1, y2)) {}
        inline bool in(qreal x, qreal y) const { return x >= x1 && x <= x2 && y >= y1 && y <= y2; }
        inline bool out(qreal x, qreal y) const { return x <= x1 || x >= x2 || y <= y1 || y >= y2; }
    };
    struct AxesParallelRhomb{
        qreal x0, y0, a, b, r;
    public:
        AxesParallelRhomb(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
        inline bool in(qreal x, qreal y) const { return value(x, y) <= r; }
        inline bool out(qreal x, qreal y) const { return value(x, y) >= r; }
        inline qreal value(qreal x, qreal y) const { return a * std::abs(x - x0) + b * std::abs(y - y0); }
    };
    Parabola vert_parabola, hor_parabola;
    Line hor_line, vert_line, hor_par_line, coord_hor_line;
    Circle circle;
    VerticalLine vert_par_line, coord_vert_line;
    AxesParallelRect rect;
    AxesParallelRhomb rhomb;
};

