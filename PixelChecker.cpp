#include "PixelChecker.h"


PixelChecker::PixelChecker():
    vert_parabola(-2.5, -1, -1.5, 0, -3.5, 0),
    hor_parabola(-2.5, -2, 0, 4, -5, 4),
    hor_line(-2, 1, 1, 0),
    vert_line(-1, 3, -4, -2),
    hor_par_line(0, hor_parabola.point().x(), 1, hor_parabola.point().x()),
    coord_hor_line(0, 0, 1, 0),
    circle(-2, 2.5, 1.5),
    vert_par_line(vert_parabola.point().x()),
    coord_vert_line(0),
    rect(-2.5, -2.5, 1.5, -4.5),
    rhomb(0.5, -3.5, 3.5, -2, 6.5, -3.5) {}

bool PixelChecker::check(qreal x, qreal y) const
{
    auto tc = hor_line.over(x, y) && vert_parabola.vert_under(x, y) && circle.out(x, y);
    auto t1 = tc && vert_line.over(x, y) && vert_par_line.left(x, y);
    auto t2 = tc && vert_line.under(x, y) && hor_parabola.hor_left(x, y) && hor_par_line.over(x, y);
    auto b1 = coord_hor_line.under(x, y) && vert_line.under(x, y) && vert_parabola.vert_under(x, y) &&
              coord_vert_line.left(x, y) && hor_parabola.hor_left(x, y) && rect.out(x, y);
    auto b2 = hor_parabola.hor_right(x, y) && rect.in(x, y) && rhomb.out(x, y);
    return t1 || t2 || b1 || b2;
}

PixelChecker::Parabola::Parabola(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) {
    a = ((y3 - y1) / (x3 - x1) - (y2 - y1) / (x2 - x1)) / ((x3 * x3 - x1 * x1) / (x3 - x1) - (x2 * x2 - x1 * x1) / (x2 - x1));
    b = (y2 - y1 + x1 * x1 * a - x2 * x2 * a) / (x2 - x1);
    c = y1 - x1 * x1 * a - x1 * b;
}

QPointF PixelChecker::Parabola::point() const {
    qreal x0 = -b / (2 * a);
    return QPointF(x0, a * x0 * x0 + b * x0 + c);
}

PixelChecker::Line::Line(qreal x1, qreal y1, qreal x2, qreal y2) {
    k = (y2 - y1) / (x2 - x1);
    b = y1 - k * x1;
}

PixelChecker::AxesParallelRhomb::AxesParallelRhomb(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) {
    if (y1 == y2) tie(x1, y1) = make_tuple(x3, y2 * 2 - y3);
    if (y2 == y3) tie(x2, y2) = make_tuple(x1, y3 * 2 - x1);
    if (y3 == y1) tie(x3, y3) = make_tuple(x2, y1 * 2 - x2);
    if (y1 < y2) tie(x1, y1, x2, y2) = make_tuple(x2, y2, x1, y1);
    if (y2 < y3) tie(x2, y2, x3, y3) = make_tuple(x3, y3, x2, y2);
    if (y1 < y2) tie(x1, y1, x2, y2) = make_tuple(x2, y2, x1, y1);
    tie(x0, y0) = make_tuple(x1, y2);
    tie(a, b) = make_tuple(std::abs(y1 - y2), std::abs(x1 - x2));
    r = a * b;
}
