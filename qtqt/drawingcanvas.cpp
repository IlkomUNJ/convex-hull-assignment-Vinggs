#include "drawingcanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFont>
#include <QPen>

int orientation(QPoint p, QPoint q, QPoint r) {
    long long val = (long long)(q.y() - p.y()) * (r.x() - q.x()) -
                    (long long)(q.x() - p.x()) * (r.y() - q.y());
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent)
{
    iterationCount = 0;
    algorithmName = "None";
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        points.append(event->pos());
        convexHull.clear();
        iterationCount = 0;
        algorithmName = "Input Mode";
        update();
    }
}

void DrawingCanvas::computeJarvisMarch()
{
    if (points.size() < 3) {
        convexHull.clear();
        return;
    }

    convexHull.clear();

    int l = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].x() < points[l].x()) {
            l = i;
        }
    }

    int p = l, q;
    do {
        convexHull.append(points[p]);
        q = (p + 1) % points.size();

        for (int i = 0; i < points.size(); i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }
        p = q;
    } while (p != l);
}

void DrawingCanvas::computeSlowConvexHull()
{
    if (points.size() < 3) {
        iterationCount = 0;
        return;
    }

    int tempIterationCount = 0;

    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points.size(); ++j) {
            if (i == j) continue;

            for (int k = 0; k < points.size(); ++k) {
                if (k == i || k == j) continue;

                tempIterationCount++;
            }
        }
    }
    iterationCount = tempIterationCount;

    computeJarvisMarch();
}

void DrawingCanvas::runSimulation()
{
    if (points.size() < 3) {
        algorithmName = "Need 3+ points!";
        update();
        return;
    }

    computeSlowConvexHull();

    algorithmName = "O(N^3) Brute-Force Test Completed";

    update();
}

void DrawingCanvas::clearCanvas()
{
    points.clear();
    convexHull.clear();
    iterationCount = 0;
    algorithmName = "Canvas Cleared";
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::red, 8));
    for (const QPoint &p : points) {
        painter.drawPoint(p);
    }

    if (convexHull.size() > 1) {
        painter.setPen(QPen(Qt::darkCyan, 3));

        for (int i = 0; i < convexHull.size(); ++i) {
            QPoint p1 = convexHull[i];
            QPoint p2 = convexHull[(i + 1) % convexHull.size()];
            painter.drawLine(p1, p2);
        }

        painter.setPen(QPen(Qt::magenta, 10));
        for (const QPoint &p : convexHull) {
            painter.drawPoint(p);
        }
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));

    QString statusText = QString("Status: %1 (Points: %2)").arg(algorithmName).arg(points.size());
    painter.drawText(this->rect().adjusted(10, 10, -10, -10), Qt::AlignTop | Qt::AlignLeft, statusText);

    if (iterationCount > 0) {
        QString iterText = QString("Total Comparisons (%1): %2").arg(algorithmName).arg(iterationCount);
        painter.drawText(this->rect().adjusted(10, 30, -10, -10), Qt::AlignTop | Qt::AlignLeft, iterText);
    }
}
