#include "pointcounter.h"
#include <vector>
#include <algorithm>
using namespace std;

void makeUniqueAndSorted(vector<int> &v) {
    std::sort(begin(v), end(v));
    v.erase(std::unique(begin(v), end(v)), end(v));
}

bool comparePoints(const QPoint &a, const QPoint &b) {
    if (a.x() == b.x()) {
        return a.y() < b.y();
    }

    return a.x() < b.x();
}

void PointCounter::processPoints(QVector<QPoint> *pointsRef) {
    xCoords.clear();
    yCoords.clear();
    countMap.clear();

    vector<QPoint> points;

    for (int i = 0; i < pointsRef->count(); i++) {
        auto point = pointsRef->at(i);

        xCoords.push_back(point.x());
        yCoords.push_back(point.y());
        points.push_back(point);
    }

    makeUniqueAndSorted(xCoords);
    makeUniqueAndSorted(yCoords);
    sort(points.begin(), points.end(), comparePoints);

    if (points.size() == 0) {
        return;
    }

    auto xPos = 0;
    auto yPos = 0;

    countMap.push_back(vector<int>(yCoords.size()));

    for (size_t i = 0; i < points.size(); i++) {
        auto point = points[i];
        auto x = point.x();
        auto y = point.y();

        while(xCoords[xPos] < x) {
            countMap.push_back(vector<int>(yCoords.size()));
            xPos++;
            yPos = 0;
        }

        while(yCoords[yPos] < y) {
            yPos++;
        }

        countMap[xPos][yPos]++;
    }

    for (size_t i = 1; i < xCoords.size(); i++) {
        countMap[i][0] += countMap[i-1][0];
    }
    for (size_t i = 1; i < yCoords.size(); i++) {
        countMap[0][i] += countMap[0][i-1];
    }

    for (size_t i = 1; i < xCoords.size(); i++) {
        for (size_t j = 1; j < yCoords.size(); j++) {
            countMap[i][j] += countMap[i][j-1] + countMap[i-1][j] - countMap[i-1][j-1];
        }
    }
}

size_t findInsertionIndex(vector<int> array, int element) {
    size_t start = 0;
    size_t end = array.size();
    size_t mid = (start + end) / 2;

    while (start != end)
    {
        if (element >= array[mid] && element <= array[min(mid + 1, array.size() - 1)])
        {
            start = mid + 1;
            end = start;
        }
        else if (element > array[mid])
        {
            start = mid + 1;
            mid += (end - mid) / 2;
        }
        else
        {
            end = mid;
            mid = start + (end - start) / 2;
        }
    }

    return start;
}

int PointCounter::getPointsCount(QPoint point) {
    auto x = point.x();
    auto y = point.y();

    int xPos = findInsertionIndex(xCoords, x);
    int yPos = findInsertionIndex(yCoords, y);

    if (xPos == xCoords.size() || xCoords[xPos] != x) xPos--;
    if (yPos == yCoords.size() || yCoords[yPos] != y) yPos--;

    if (xPos < 0 || yPos < 0) {
        return 0;
    }

    return countMap[xPos][yPos];
}

QRect nomalizeRect(QRect rect) {
    auto x1 = rect.topLeft().x();
    auto x2 = rect.bottomRight().x();
    auto y1 = rect.topLeft().y();
    auto y2 = rect.bottomRight().y();

    auto p1 = QPoint(min(x1, x2), min(y1, y2));
    auto p2 = QPoint(max(x1, x2), max(y1, y2));

    return QRect(p1, p2);
}

int PointCounter::getPointsCount(QRect rect) {
    rect = nomalizeRect(rect);

    auto p1 = rect.topLeft();
    auto p2 = rect.topRight();
    auto p3 = rect.bottomLeft();
    auto p4 = rect.bottomRight();

    return getPointsCount(p4) + getPointsCount(p1) - getPointsCount(p2) - getPointsCount(p3);
}
