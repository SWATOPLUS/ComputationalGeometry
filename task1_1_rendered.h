#ifndef TASK1_1_RENDERED_H
#define TASK1_1_RENDERED_H

#include <QWidget>
#include <QPainter>

class Task1_1_Rendered : public QWidget
{
    Q_OBJECT
public:
    Task1_1_Rendered(QVector<QPoint> *points, QWidget *parent = nullptr) : QWidget(parent) {
        _points = points;
        _pointSize = 1;
    }

    void paintEvent(QPaintEvent *event){
        QPainter painter(this);

        for (int i =0; i < _points->count();i++) {
            auto p = _points->at(i);

            if (_pointSize > 1) {
                painter.drawEllipse(p, _pointSize, _pointSize);
            } else {
                painter.drawPoint(p);
            }
        }
    }

    void setPointSize(int size) {
        _pointSize = size;
    }

    int getPointSize() {
        return _pointSize;
    }

private:
    QVector<QPoint> *_points;
    int _pointSize;
signals:

};

#endif // TASK1_1_RENDERED_H
