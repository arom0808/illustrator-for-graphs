#pragma once

#include "PixelChecker.h"
#include "Approximator.h"

#include <QImage>
#include <QColor>

class GraphPainter
{
public:
    GraphPainter(QSize max_size, qreal min_input_scale, qreal max_input_scale, qreal min_scale, qreal max_scale,
                 qreal base_input_scale, qreal base_pixels_scale);
    void draw(QSize size, uint32_t input_scale);
    const QImage& get_image() const;

    static constexpr QColor true_color{73, 236, 41}, false_color{41, 145, 236}, coords_color{0, 0, 0};

private:
    QImage img;
    PixelChecker pixel_checker;
    Approximator approximator;
};

