#include "paintwidget.h"
#include "ui_paintwidget.h"
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paintWidget)
{
    ui->setupUi(this);
}

PaintWidget::~PaintWidget()
{
    delete ui;
}
void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0,0,_img);
    qDebug()<<"paintEvent";
}

void PaintWidget::paintFrame(QImage img)
{
    _img = img;
    update();
}
