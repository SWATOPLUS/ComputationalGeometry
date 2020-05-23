#ifndef TASK1_1_H
#define TASK1_1_H

#include <QWidget>

namespace Ui {
class Task1_1;
}

class Task1_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Task1_1(QWidget *parent = nullptr);
    ~Task1_1();

private:
    Ui::Task1_1 *ui;
};

#endif // TASK1_1_H
