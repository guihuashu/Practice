#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMutex>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    virtual void paintEvent(QPaintEvent *e);
    void setPix(QPixmap pix);
    QMutex mutex;

private:
    Ui::Widget *ui;
    QPixmap pix;
};

#endif // WIDGET_H
