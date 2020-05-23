#include "task1_1.h"
#include "ui_task1_1.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QTabWidget>

Task1_1::Task1_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task1_1)
{
    ui->setupUi(this);

    points = new QVector<QPoint>();
    renderer = new Task1_1_Rendered(points);
    renderer->setPointSize(1);
    ui->verticalLayout->addWidget(renderer);
}

Task1_1::~Task1_1()
{
    delete points;
    delete ui;
}

void Task1_1::on_applyButton_clicked()
{
    auto newSize = ui->pointCountSpinBox->value();
    auto oldSize = points->count();

    if (newSize < oldSize){
        points->resize(newSize);
    } else {
        auto widget = renderer->size();
        auto maxX = widget.rwidth();
        auto maxY = widget.height();

        while (oldSize < newSize) {
            auto x = rand() % maxX;
            auto y = rand() % maxY;

            points->append(QPoint(x, y));
            oldSize++;
        }
    }

    renderer->repaint();
}

void Task1_1::on_isBigCircleCheckBox_toggled(bool checked)
{
    if (checked) {
        renderer->setPointSize(3);
    } else {
        renderer->setPointSize(1);
    }

    renderer->repaint();
}
