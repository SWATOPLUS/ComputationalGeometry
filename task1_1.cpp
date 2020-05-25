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
    renderer = new Task1_1_Rendered(points, this);
    renderer->setPointSize(1);
    ui->verticalLayout->addWidget(renderer);

    pointCounter = new PointCounter();
    pointCounter->processPoints(points);
}

Task1_1::~Task1_1()
{
    delete pointCounter;
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

    pointCounter->processPoints(points);

    repaint();
}

void Task1_1::on_isBigCircleCheckBox_toggled(bool checked)
{
    if (checked) {
        renderer->setPointSize(3);
    } else {
        renderer->setPointSize(1);
    }

    repaint();
}

void Task1_1::paintEvent(QPaintEvent *event)
{
    auto counter = 0;

    if (renderer->isRectReady()) {
        auto rect = renderer->getMainRect();


        /**** trivial calculation
        for (int i = 0; i < points->count(); i++) {
            auto point = points->at(i);

            if (rect.contains(point)) {
              counter++;
            }
        }
        */
        counter = pointCounter->getPointsCount(rect);
    } else {
        auto mainPoint = renderer->getMainPoint();
        counter = pointCounter->getPointsCount(mainPoint);
    }

    ui->selectedPointsLabel->setText("Selected points: " + QString::number(counter));

    QWidget::paintEvent(event);
}
