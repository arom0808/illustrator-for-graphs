#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    graph_painter = new GraphPainter(ui->graphicsView->maximumSize(), ui->horizontalSlider->minimum(), min_pix_scale);
    ui->graphicsView->setScene(scene);
    draw();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    draw();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) { draw(); }

void MainWindow::on_checkBox_stateChanged(int arg1) { draw(); }

void MainWindow::draw()
{
    ui->label->setText(QString::number(graph_painter->get_scale(ui->horizontalSlider->value())) + "px / 1");
    graph_painter->draw(ui->graphicsView->contentsRect().size(), ui->horizontalSlider->value(), ui->checkBox->isChecked());
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

