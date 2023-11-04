#pragma once

#include <QObject>
#include <QPointF>
#include <functional>
#include <algorithm>

class PixelChecker
{
public:
    bool check(qreal x, qreal y) const;
private:
    struct Circle {
    public:
        qreal x0, y0, r;
        Circle(qreal x0, qreal y0, qreal r) : x0(x0), y0(y0), r(r) {}
        bool in(qreal x, qreal y) { return (x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r; }
        bool out(qreal x, qreal y) { return (x - x0) * (x - x0) + (y - y0) * (y - y0) >= r * r; }
    };
    struct Parabola {
    private:
        QPointF _point(){
            qreal x0 = -b / (2 * a);
            return QPointF(x0, a * x0 * x0 + b * x0 + c);
        }
    public:
        qreal a, b, c;
        QPointF point;
        Parabola(qreal a, qreal b, qreal c) : a(a), b(b), c(c), point(_point()) {}
        Parabola(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) {
            a = ((y3 - y1) / (x3 - x1) - (y2 - y1) / (x2 - x1)) / ((x3 * x3 - x1 * x1) / (x3 - x1) - (x2 * x2 - x1 * x1) / (x2 - x1));
            b = (y2 - y1 + x1 * x1 * a - x2 * x2 * a) / (x2 - x1);
            c = y1 - x1 * x1 * a - x1 * b;
            point = _point();
        }
        bool vert_over(qreal x, qreal y) { return y >= a * x * x + b * x + c; }
        bool vert_under(qreal x, qreal y) { return y <= a * x * x + b * x + c; }
        bool hor_right(qreal x, qreal y) { return x >= a * y * y + b * y + c; }
        bool hor_left(qreal x, qreal y) { return x <= a * y * y + b * y + c; }
    };
    struct VerticalLine {
    public:
        qreal x0;
        VerticalLine(qreal x0) : x0(x0) {}
        bool left(qreal x, qreal y) { return x <= x0; }
        bool right(qreal x, qreal y) { return x >= x0; }
    };

    struct Line {
    public:
        qreal k, b;
        Line(qreal k, qreal b) : k(k), b(b) {}
        Line(qreal x1, qreal y1, qreal x2, qreal y2) {
            k = (y2 - y1) / (x2 - x1);
            b = y1 - k * x1;
        }
        bool over(qreal x, qreal y) { return y >= k * x + b; }
        bool under(qreal x, qreal y) { return y <= k * x + b; }
    };
};

