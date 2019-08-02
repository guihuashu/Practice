#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <thread>
#include <iostream>
#include <QThread>
#include <QAudioOutput>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void initInput();
    void initOutput();

    ~Widget();
    void dump(QString str);
    void dump_fmt(QAudioFormat &inFmt);
    Ui::Widget *ui;

public:
    QAudioFormat inFmt;
    QAudioInput *input;
    QIODevice *inIo;

    QAudioFormat outFmt;
    QAudioOutput *output;
    QIODevice *outIo;
};

#endif // WIDGET_H
