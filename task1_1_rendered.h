#ifndef TASK1_1_RENDERED_H
#define TASK1_1_RENDERED_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class Task1_1_Rendered : public QWidget
{
    Q_OBJECT
public:
    Task1_1_Rendered(QVector<QPoint> *points, QWidget *parent = nullptr) : QWidget(parent) {
        _points = points;
        _pointSize = 1;
    }

    void mousePressEvent(QMouseEvent *event){
        mousePoint = QPoint(event->x(), event->y());
        dragMode = false;
    }

    void mouseMoveEvent(QMouseEvent *event){
        if ((event->buttons() == Qt::LeftButton) && rectState == 2) {
            auto newPoint = QPoint(event->x(), event->y());

            auto xOffset = newPoint.x() - mousePoint.x();
            auto yOffset = newPoint.y() - mousePoint.y();

            auto rect = QRect();
            rect.setX(mainRect.x() + xOffset);
            rect.setY(mainRect.y() + yOffset);
            rect.setSize(mainRect.size());
            mainRect = rect;

            mousePoint = newPoint;
            dragMode = true;

            parentWidget()->repaint();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event){
        auto newPoint = QPoint(event->x(), event->y());

        if (mousePoint == newPoint && !dragMode) {
            if (rectState != 1) {
                rectState = 1;
                mainRect.setTopLeft(mousePoint);
            } else {
                rectState = 2;
                mainRect.setBottomRight(mousePoint);
            }

            parentWidget()->repaint();
        }
    }

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);

        painter.setPen(QPen(QColor::fromRgb(0, 0, 0)));
        painter.setBrush(QBrush(QColor::fromRgb(0, 0, 0), Qt::BrushStyle::NoBrush));

        for (int i = 0; i < _points->count();i++) {
            auto p = _points->at(i);

            if (_pointSize > 1) {
                painter.drawEllipse(p, _pointSize, _pointSize);
            } else {
                painter.drawPoint(p);
            }
        }

        painter.setPen(QPen(QColor::fromRgb(255, 0, 0)));

        if (rectState == 1) {
            painter.setBrush(QBrush(QColor::fromRgb(255, 0, 0)));
            painter.drawEllipse(mainRect.topLeft(), 5, 5);
        } else if (rectState == 2) {
            painter.drawRect(mainRect);
        }


    }

    void setPointSize(int size) {
        _pointSize = size;
    }

    int getPointSize() {
        return _pointSize;
    }

    QRect getMainRect() {
        return mainRect;
    }

    bool isRectReady() {
        return rectState == 2;
    }

private:
    bool dragMode = false;
    int rectState = 0;
    QPoint mousePoint;
    QRect mainRect;
    QVector<QPoint> *_points;
    int _pointSize;
signals:

};

#endif // TASK1_1_RENDERED_H
