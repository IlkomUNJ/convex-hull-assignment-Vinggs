#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPoint>
#include <QVector>

class DrawingCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    QSize sizeHint() const override { return QSize(800, 600); }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void runSimulation();
    void clearCanvas();

private:
    QVector<QPoint> points;
    QVector<QPoint> convexHull;
    int iterationCount;
    QString algorithmName;

    void computeJarvisMarch();
    void computeSlowConvexHull();
};

int orientation(QPoint p, QPoint q, QPoint r);

#endif // DRAWINGCANVAS_H
