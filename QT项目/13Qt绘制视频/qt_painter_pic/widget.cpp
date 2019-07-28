#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    qDebug()<<"paintEvent";
    QPainter painter(this);
    painter.drawPixmap(0,0, pix);
}

void Widget::setPix(QPixmap pix)
{
    this->pix = pix;
}
