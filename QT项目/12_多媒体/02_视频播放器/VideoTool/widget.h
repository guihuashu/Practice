#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPaintEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual void paintEvent(QPaintEvent *e);

private slots:
    void on_btopen_clicked();
    void on_bt_stop_clicked();
    void on_bt_start_clicked();

    void on_hScrollBar_valueChanged(int value);

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QVideoWidget *mwidget;
};

#endif // WIDGET_H
