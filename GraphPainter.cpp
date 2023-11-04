#include "GraphPainter.h"


GraphPainter::GraphPainter(QSize max_size, qreal min_input_scale, qreal max_input_scale, qreal min_scale, qreal max_scale,
                           qreal base_input_scale, qreal base_pixels_scale)
    : img(max_size, QImage::Format_RGB32)
    , approximator(min_input_scale, min_scale * base_pixels_scale, base_input_scale, base_pixels_scale,
            max_input_scale, max_scale * base_pixels_scale) {}

void GraphPainter::draw(QSize size, uint32_t input_scale)
{
    qreal scale = approximator(input_scale);
    for (int32_t pix_x = 0; pix_x < size.width(); ++pix_x) {
        for (int32_t pix_y = 0; pix_y < size.height(); ++pix_y) {
            qreal x = pix_x - size.width() / 2, y = (size.height() - pix_y - 1) - size.height() / 2;
            img.setPixelColor(pix_x, pix_y, pixel_checker.check(x / scale, y / scale) ? true_color : false_color);
        }
    }
//    for (int32_t pix_x = 0; pix_x < size.width(); ++pix_x) img.setPixelColor(pix_x, size.height() / 2, coords_color);
//    for (int32_t pix_y = 0; pix_y < size.height(); ++pix_y) img.setPixelColor(size.width() / 2, pix_y, coords_color);
}

const QImage &GraphPainter::get_image() const
{
    return img;
}
