#include "GraphPainter.h"


GraphPainter::GraphPainter(QSize max_size, qreal min_input_scale, qreal min_pix_scale)
    : img(max_size, QImage::Format_RGB32), k(min_pix_scale / min_input_scale){}

void GraphPainter::draw(QSize size, uint32_t input_scale, bool axes)
{
    qreal scale = get_scale(input_scale);
    for (int32_t pix_x = 0; pix_x < size.width(); ++pix_x) {
        for (int32_t pix_y = 0; pix_y < size.height(); ++pix_y) {
            qreal x = pix_x - size.width() / 2, y = (size.height() - pix_y - 1) - size.height() / 2;
            img.setPixelColor(pix_x, pix_y, pixel_checker.check(x / scale, y / scale) ? true_color : false_color);
        }
    }
    if (axes) {
        int32_t min_x = -qreal(size.width() / 2) / scale - 0.5, max_x = qreal(size.width() / 2) / scale + 0.5,
            min_y = -qreal(size.height() / 2) / scale - 0.5, max_y = qreal(size.height() / 2) / scale + 0.5;
        int32_t len = max<int32_t>(scale / 5, 1);
        bool cond = false;
        for (int32_t x = min_x, pix_x = x * scale + size.width() / 2; x <= max_x; ++x, pix_x = x * scale + size.width() / 2) {
            if (pix_x < 0 || pix_x >= size.width()) continue;
            for (int32_t pix_y = 0; pix_y < size.height(); ++pix_y) {
                if (cond || x == 0) img.setPixelColor(pix_x, pix_y, coords_color);
                if (pix_y % len == 0) cond = !cond;
            }
        }
        for (int32_t y = min_y, pix_y = size.height() / 2 - y * scale; y <= max_y; ++y, pix_y = size.height() / 2 - y * scale) {
            if (pix_y < 0 || pix_y >= size.height()) continue;
            for (int32_t pix_x = 0; pix_x < size.width(); ++pix_x) {
                if (cond || y == 0) img.setPixelColor(pix_x, pix_y, coords_color);
                if (pix_x % len == 0) cond = !cond;
            }
        }
    }
}

const QImage &GraphPainter::get_image() const
{
    return img;
}
