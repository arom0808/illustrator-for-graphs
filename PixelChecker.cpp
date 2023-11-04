#include "PixelChecker.h"


bool PixelChecker::check(qreal x, qreal y) const
{
    Parabola vert_parabola(-2.5, -1, -1.5, 0, -3.5, 0), hor_parabola(-2.5, -2, 0, 4, -5, 4);
    Line hor_line(-2, 1, 1, 0), vert_line(-1, 3, -4, -2), hor_par_line(0, hor_parabola.point.x(), 1, hor_parabola.point.x());
    Circle circle(-2, 2.5, 1.5);
    VerticalLine vert_par_line(vert_parabola.point.x());
    auto cvphd = hor_line.over(x, y) && vert_parabola.vert_under(x, y) && circle.out(x, y);
    auto t1 = cvphd && vert_line.over(x, y) && vert_par_line.left(x, y);
    auto t2 = cvphd && vert_line.under(x, y) && hor_parabola.hor_left(x, y) && hor_par_line.over(x, y);
    return t1 || t2;
//    return hor_line.over(x, y) && vert_parabola.vert_under(x, y) && circle.out(x, y) && vert_line.under(x, y) && hor_parabola.hor_left(x, y);
//    return hor_line.over(x, y) && vert_parabola.vert_under(x, y) && circle.out(x, y) && vert_line.under(x, y) && hor_parabola.hor_left(x, y);
//        , circle.out, vert_line.under, hor_parabola.hor_left};
//    return top_part.intersect(x, y);
}
