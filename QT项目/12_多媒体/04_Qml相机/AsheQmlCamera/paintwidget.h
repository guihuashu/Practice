#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QVideoFrame>
#include <QPainter>
#include <QImage>
namespace Ui {
class paintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();
    virtual void paintEvent(QPaintEvent *event);
    void paintFrame(QImage img);

private:
    Ui::paintWidget *ui;
    QImage _img;
};

#endif // PAINTWIDGET_H
