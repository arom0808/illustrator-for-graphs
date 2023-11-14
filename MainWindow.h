#pragma once

#include "GraphPainter.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_stateChanged(int arg1);

private:
    void draw();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    GraphPainter *graph_painter;

    static constexpr qreal min_scale = 0.1, base_pixels_scale = 10, min_pix_scale = min_scale * base_pixels_scale;
};
