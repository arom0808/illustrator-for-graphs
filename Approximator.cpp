#include "Approximator.h"

Approximator::Approximator(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3) {
    if (x1 > x2) std::tie(x1, y1, x2, y2) = std::make_tuple(x2, y2, x1, y1);
    if (x2 > x3) std::tie(x2, y2, x3, y3) = std::make_tuple(x3, y3, x2, y2);
    if (x1 > x2) std::tie(x1, y1, x2, y2) = std::make_tuple(x2, y2, x1, y1);
    std::tie(this->x1, this->y1, this->x2, this->y2, this->x3, this->y3) = std::make_tuple(x1, y1, x2, y2, x3, y3);
}

//I tried to make a smoother approximation, but the quadratic regression can go into negative values, and others have too large an average error.
qreal Approximator::operator()(qreal x) const
{
    if (x < x2) return y1 + (x - x1) / (x2 - x1) * (y2 - y1);
    return y2 + (x - x2) / (x3 - x2) * (y3 - y2);
}
