#ifndef POINTCOUNTER_H
#define POINTCOUNTER_H

#include <QPoint>
#include <QVector>
#include <QRect>

class PointCounter
{
public:
    void processPoints(QVector<QPoint> *pointsRef);
    int getPointsCount(QPoint point);
    int getPointsCount(QRect rect);

private:
    std::vector<std::vector<int> > countMap;
    std::vector<int> xCoords;
    std::vector<int> yCoords;
};

#endif // POINTCOUNTER_H
