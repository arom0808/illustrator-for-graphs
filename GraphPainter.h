#pragma once

#include "PixelChecker.h"

#include <QImage>
#include <QColor>

class GraphPainter
{
public:
    GraphPainter(QSize max_size, qreal min_input_scale, qreal min_pix_scale);
    void draw(QSize size, uint32_t input_scale, bool axes);
    const QImage& get_image() const;
    uint32_t get_scale(uint32_t input_scale) const { return k * input_scale; }

    static constexpr QColor true_color{73, 236, 41}, false_color{41, 145, 236}, coords_color{0, 0, 0};

private:
    QImage img;
    PixelChecker pixel_checker;
    qreal k;
};

