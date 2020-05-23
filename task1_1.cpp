#include "task1_1.h"
#include "ui_task1_1.h"

Task1_1::Task1_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task1_1)
{
    ui->setupUi(this);
}

Task1_1::~Task1_1()
{
    delete ui;
}
