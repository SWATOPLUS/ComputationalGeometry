#ifndef TASK1_1_H
#define TASK1_1_H

#include <QWidget>
#include "task1_1_rendered.h"

namespace Ui {
class Task1_1;
}

class Task1_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Task1_1(QWidget *parent = nullptr);
    ~Task1_1();

private slots:
    void on_applyButton_clicked();

    void on_isBigCircleCheckBox_toggled(bool checked);

private:
    Ui::Task1_1 *ui;
    QVector<QPoint> *points;
    Task1_1_Rendered *renderer;
};

#endif // TASK1_1_H
