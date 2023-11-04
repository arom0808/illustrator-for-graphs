#pragma once

#include <QObject>
#include <tuple>

class Approximator
{
public:
    Approximator(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3);
    qreal operator()(qreal x) const;

private:
    qreal x1, y1, x2, y2, x3, y3;
};

