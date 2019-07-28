#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
void Widget::paintEvent(QPaintEvent *e)
{
    mwidget->resize(this->size());   // 必须设置, 否则显示不出图像
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mwidget = new QVideoWidget(ui->movieWidget);
    player = new QMediaPlayer(ui->movieWidget);
    player->setVideoOutput(mwidget);
    player->setVolume(50);
    mwidget->show();
    ui->hScrollBar->setMinimum(0);
    ui->hScrollBar->setMaximum(200);
}

Widget::~Widget()
{
    delete ui;
}

// 打开
void Widget::on_btopen_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

// 暂停
void Widget::on_bt_stop_clicked()
{
    ui->bt_start->setEnabled(true);
    ui->bt_stop->setEnabled(false);
    player->pause();
}

// 开始
void Widget::on_bt_start_clicked()
{
    ui->bt_start->setEnabled(false);
    ui->bt_stop->setEnabled(true);
    player->play();
}



void Widget::on_hScrollBar_valueChanged(int value)
{
    player->setVolume(value);
}
