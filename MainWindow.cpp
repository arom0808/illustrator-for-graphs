#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    graph_painter = new GraphPainter(ui->graphicsView->maximumSize(), ui->horizontalSlider->minimum(),
                                     ui->horizontalSlider->maximum(), min_scale, max_scale, ui->horizontalSlider->value(),
                                     base_pixels_scale);
    ui->graphicsView->setScene(scene);
    draw();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    draw();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    draw();
}

void MainWindow::draw()
{
    graph_painter->draw(ui->graphicsView->contentsRect().size(), ui->horizontalSlider->value());
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(graph_painter->get_image()));
    ui->graphicsView->setSceneRect(ui->graphicsView->contentsRect());
}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete graph_painter;
}
