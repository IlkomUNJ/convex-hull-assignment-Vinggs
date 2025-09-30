#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "drawingcanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Computer Graphics Simulation");

    QWidget *centralWidget = new QWidget(&window);

    DrawingCanvas *canvas = new DrawingCanvas(centralWidget);

    QPushButton *runButton = new QPushButton("Fix Convex Hull");
    QPushButton *clearButton = new QPushButton("Clear Canvas");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(runButton);
    buttonLayout->addWidget(clearButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(canvas, 1);
    mainLayout->addLayout(buttonLayout);

    QObject::connect(runButton, &QPushButton::clicked, canvas, &DrawingCanvas::runSimulation);
    QObject::connect(clearButton, &QPushButton::clicked, canvas, &DrawingCanvas::clearCanvas);

    window.setCentralWidget(centralWidget);
    window.show();

    return a.exec();
}
